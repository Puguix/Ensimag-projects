using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common;
using NeuralNetwork.Common.JsonUtils;
using NeuralNetwork.Common.Serialization;
using NeuralNetwork.Serialization;
using Prism.Commands;
using Prism.Mvvm;
using System.IO;
using System.Text.Json;
using System.Windows.Forms;

namespace BooleanFunctionTester
{
    internal class MainWindowViewModel : BindableBase
    {
        private INetwork currentNetwork;
        private double networkEvaluation;
        private double networkConfidence;
        public DelegateCommand LoadCommand { get; }
        public DelegateCommand EvaluateCommand { get; }
        public SerializedNetwork InitialSerializedNetwork { get; private set; }
        public UserInput UserInput { get; }
        public INetwork CurrentNetwork
        {
            get => currentNetwork;
            private set
            {
                SetProperty(ref currentNetwork, value);
                EvaluateCommand.RaiseCanExecuteChanged();
            }
        }

        public double NetworkEvaluation
        {
            get => networkEvaluation;
            set => SetProperty(ref networkEvaluation, value);
        }
        public double NetworkRawOutput
        {
            get => networkConfidence;
            set => SetProperty(ref networkConfidence, value);
        }

        public MainWindowViewModel()
        {
            UserInput = new UserInput();
            LoadCommand = new DelegateCommand(LoadNetwork);
            EvaluateCommand = new DelegateCommand(ForwardPropagate, CanForwardPropagate);
        }

        private bool CanForwardPropagate()
        {
            return CurrentNetwork != null && CurrentNetwork?.Layers[0].InputSize == 2 && CurrentNetwork?.Output.RowCount == 1;
        }

        private void ForwardPropagate()
        {
            var input = Matrix<double>.Build.Dense(2, 1);
            input[0, 0] = UserInput.FirstArgument;
            input[1, 0] = UserInput.SecondArgument;
            CurrentNetwork.Propagate(input);
            NetworkRawOutput = CurrentNetwork.Output[0, 0];
            NetworkEvaluation = NetworkRawOutput < 0.5 ? 0 : 1;
        }

        private void LoadNetwork()
        {
            using (var dialog = new OpenFileDialog())
            {
                var result = dialog.ShowDialog();
                if (result == DialogResult.OK)
                {
                    InitialSerializedNetwork = JsonIO.DeserializeNetworkFromFile(dialog.FileName);
                    CurrentNetwork = NetworkDeserializer.Deserialize(InitialSerializedNetwork);
                    CurrentNetwork.BatchSize = 1;
                }
            }
        }
    }
}
