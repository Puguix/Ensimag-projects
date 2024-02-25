using DataProviders;
using LiveChartsCore;
using LiveChartsCore.SkiaSharpView;
using LiveChartsCore.SkiaSharpView.SKCharts;
using NeuralNetwork.Common;
using NeuralNetwork.Common.JsonUtils;
using NeuralNetwork.Common.Serialization;
using NeuralNetwork.Serialization;
using Newtonsoft.Json;
using Prism.Commands;
using Prism.Mvvm;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Configuration;
using System.IO;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Media;
using Trainer;
using Trainer.CostFunctions;
using Visualizer.NetworkInfo;
using Visualizer.Training;

namespace Visualizer
{
    internal class MainWindowViewModel : BindableBase
    {
        private ObservableCollection<ISeries> collection;
        private INetwork currentNetwork;
        private NetworkSummary networkSummary;
        private int epochNb;
        private int epochsBetweenValidations;
        private SplitData splitData;
        private string dataInfo;
        private string trainInfo;
        private int currentEpoch;

        public DelegateCommand GoCommand { get; }
        public DelegateCommand ClearCommand { get; }
        public DelegateCommand SaveCommand { get; }
        public DelegateCommand LoadCommand { get; }
        public DelegateCommand GetDataCommand { get; }
        public DelegateCommand ResetCommand { get; }

        public int CurrentEpoch
        {
            get => currentEpoch;
            set => SetProperty(ref currentEpoch, value);
        }

        public ObservableCollection<ISeries> Collection
        {
            get => collection;
            private set => SetProperty(ref collection, value);
        }

        public SplitData SplitData
        {
            get => splitData;
            set
            {
                SetProperty(ref splitData, value);
                GoCommand.RaiseCanExecuteChanged();
            }
        }

        public string DataInfo
        {
            get => dataInfo;
            set => SetProperty(ref dataInfo, value);
        }

        public string TrainInfo
        {
            get => trainInfo;
            set => SetProperty(ref trainInfo, value);
        }

        public int EpochNb { get => epochNb; set => SetProperty(ref epochNb, value); }
        public int EpochsBetweenValidations { get => epochsBetweenValidations; set => SetProperty(ref epochsBetweenValidations, value); }

        public NetworkSummary NetworkSummary
        {
            get => networkSummary;
            set => SetProperty(ref networkSummary, value);
        }

        public INetwork CurrentNetwork
        {
            get => currentNetwork;
            private set
            {
                SetProperty(ref currentNetwork, value);
                GoCommand.RaiseCanExecuteChanged();
                SaveCommand.RaiseCanExecuteChanged();
                ResetCommand.RaiseCanExecuteChanged();
                NetworkSummary = new NetworkSummary(value);
            }
        }

        public SerializedNetwork InitialSerializedNetwork { get; private set; }
        public TrainingDataViewModel Training { get; }

        public MainWindowViewModel()
        {
            GoCommand = new DelegateCommand(async () => await TrainNetwork(), DataNetworkFit);
            SaveCommand = new DelegateCommand(SaveNetwork, NetworkNotNull);
            ResetCommand = new DelegateCommand(ResetNetwork, NetworkNotNull);
            ClearCommand = new DelegateCommand(ClearSeries);
            LoadCommand = new DelegateCommand(LoadNetwork);
            GetDataCommand = new DelegateCommand(GetData);
            Collection = new ObservableCollection<ISeries>();
            Training = new TrainingDataViewModel();
            EpochNb = 1000;
            EpochsBetweenValidations = 10;
            DataInfo = "No data loaded";
            TrainInfo = "Missing data and/or network";
        }

        private bool DataNetworkFit()
        {
            if (SplitData == null || CurrentNetwork == null)
            {
                return false;
            }
            var result = CurrentNetwork.Layers[0].InputSize == SplitData.TrainingData.Inputs.RowCount &&
                CurrentNetwork.Output.RowCount == SplitData.TrainingData.Outputs.RowCount;
            if (result)
            {
                TrainInfo = "Training can start";
            }
            else
            {
                TrainInfo = "Input/output mismatch";
            }
            return result;
        }

        private void ResetNetwork()
        {
            CurrentNetwork = NetworkDeserializer.Deserialize(InitialSerializedNetwork);
        }

        private void GetData()
        {
            SplitData = Training.SelectedDataProvider.DataProvider.GetData();
            DataInfo = $"Loaded data from {Training.SelectedDataProvider.Name} provider";
        }

        private bool NetworkNotNull() => CurrentNetwork != null;

        private void LoadNetwork()
        {
            using (var dialog = new OpenFileDialog())
            {
                dialog.InitialDirectory = ConfigurationManager.AppSettings["AbsoluteOutputPath"];
                var result = dialog.ShowDialog();
                if (result == DialogResult.OK)
                {
                    InitialSerializedNetwork = JsonIO.DeserializeNetworkFromFile(dialog.FileName);
                    CurrentNetwork = NetworkDeserializer.Deserialize(InitialSerializedNetwork);
                }
            }
        }

        private void SaveNetwork()
        {
            using (var dialog = new SaveFileDialog())
            {
                dialog.InitialDirectory = ConfigurationManager.AppSettings["AbsoluteOutputPath"];
                var result = dialog.ShowDialog();
                if (result == DialogResult.OK)
                {
                    JsonIO.SerializeNetworkToFile(NetworkSerializer.Serialize(CurrentNetwork), $"{dialog.FileName}.json");
                }
            }
        }

        private void ClearSeries()
        {
            Collection.Clear();
        }

        private async Task TrainNetwork()
        {
            var summary = await Task.Run(() => RunTrainingProcedure());
            UpdateCollection(summary.ValidationErrors, "Validation");
            UpdateCollection(summary.TrainingErrors, "Training");
        }

        private ErrorSummary RunTrainingProcedure()
        {
            var dataShuffler = Training.SelectedShuffler.Shuffler;
            var data = Training.SelectedDataProvider.DataProvider.GetData();
            var trainingData = data.TrainingData;
            var validationData = data.ValidationData;
            var runner = new NetworkTrainer(CurrentNetwork, new QuadraticError(), dataShuffler);
            int nbPts = 1 + (EpochNb-1) / EpochsBetweenValidations;
            double[] validationErrors = new double[nbPts];
            double[] trainingErrors = new double[nbPts];
            for (int i = 0; i < EpochNb; i++)
            {
                CurrentEpoch = i + 1;
                runner.Train(trainingData);
                if (i % EpochsBetweenValidations == 0)
                {
                    var currentValidationError = runner.Validate(validationData);
                    validationErrors[i / EpochsBetweenValidations] = currentValidationError;
                    var currentTrainingError = runner.Validate(trainingData);
                    trainingErrors[i / EpochsBetweenValidations] = currentTrainingError;
                }
            }
            return new ErrorSummary(validationErrors, trainingErrors);
        }

        private void UpdateCollection(double[] errors, string name)
        {
            var lineSeries = new LineSeries<double>
            {
                Values = new ObservableCollection<double>(errors),
                Fill = null,
                GeometrySize=2,
                LineSmoothness = 0,
                GeometryStroke = null,
            };
            Collection.Add(lineSeries);
        }

        private class ErrorSummary
        {
            public ErrorSummary(double[] validationErrors, double[] trainingErrors)
            {
                ValidationErrors = validationErrors;
                TrainingErrors = trainingErrors;
            }

            public double[] ValidationErrors { get; }
            public double[] TrainingErrors { get; }
        }
    }
}