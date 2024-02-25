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
    class TestConfigViewModel : BindableBase
    {
        private int batchSize;
        private EvaluationFunctionInfo selectedErrorFunction;
        public ObservableCollection<EvaluationFunctionInfo> AvailableEvaluationFunctions { get; }
        public EvaluationFunctionInfo SelectedEvaluationFunction
        {
            get => selectedErrorFunction;
            set => SetProperty(ref selectedErrorFunction, value);
        }
        public int BatchSize
        {
            get => batchSize;
            set => SetProperty(ref batchSize, value);
        }


        public TestConfigViewModel()
        {
            var service = new AvailableEvaluationFunctionsService();
            AvailableEvaluationFunctions = new ObservableCollection<EvaluationFunctionInfo>(service.GetEvaluationFunctions());
            SelectedEvaluationFunction = AvailableEvaluationFunctions.First();
            BatchSize = 1;
        }

        
    }
}
