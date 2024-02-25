using NeuralNetwork.Structure;
using NeuralNetwork.Structure.Configurations;
using Prism.Commands;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Visualizer.Configuration
{
    class MainConfigViewModel : BindableBase
    {
        public NetworkConfigViewModel NetworkConfig { get; }
        public TrainingConfigViewModel TrainingConfig { get; }
        public TestConfigViewModel TestConfig { get; }


        public MainConfigViewModel()
        {
            NetworkConfig = new NetworkConfigViewModel();
            TrainingConfig = new TrainingConfigViewModel();
            TestConfig = new TestConfigViewModel();
        }

    }
}
