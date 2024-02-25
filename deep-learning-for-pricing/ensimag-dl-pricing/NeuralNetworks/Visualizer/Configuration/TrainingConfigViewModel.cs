using NeuralNetwork.CostFunctions;
using NeuralNetwork.GradientAccelerators;
using NeuralNetwork.Structure.Configurations;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Visualizer.Services;

namespace Visualizer.Configuration
{
    class TrainingConfigViewModel : BindableBase
    {
        private int batchSize;
        private CostFunctionInfo selectedErrorFunction;
        private AcceleratorInfo selectedAccelerator;

        public ObservableCollection<CostFunctionInfo> AvailableErrorFunctions { get; }
        public ObservableCollection<AcceleratorInfo> AvailableAccelerators { get; }

        public CostFunctionInfo SelectedErrorFunction
        {
            get => selectedErrorFunction;
            set => SetProperty(ref selectedErrorFunction, value);
        }
        public int BatchSize
        {
            get => batchSize;
            set => SetProperty(ref batchSize, value);
        }

        
        public AcceleratorInfo SelectedAccelerator
        {
            get => selectedAccelerator;
            set => SetProperty(ref selectedAccelerator, value);
        }

        public TrainingConfigViewModel()
        {
            var service = new AvailableCostFunctionsService();
            AvailableErrorFunctions = new ObservableCollection<CostFunctionInfo>(service.GetErrorFunctions());
            SelectedErrorFunction = AvailableErrorFunctions.First();
            var acceleratorService = new AvailableAcceleratorsService();
            AvailableAccelerators = new ObservableCollection<AcceleratorInfo>(acceleratorService.GetAccelerators());
            SelectedAccelerator = AvailableAccelerators.First();

            BatchSize = 4;
        }

        public TrainingConfiguration MakeTrainingConfiguration()
        {
            var accelerator = SelectedAccelerator.GradientAcceleratorParameters.MakeParameters();
            return new TrainingConfiguration(BatchSize, accelerator, SelectedErrorFunction.CostFunction);
        }
    }
}
