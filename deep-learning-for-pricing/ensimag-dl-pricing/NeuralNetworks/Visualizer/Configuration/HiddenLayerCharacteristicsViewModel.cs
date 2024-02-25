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
    class HiddenLayerCharacteristicsViewModel : BindableBase
    {
        private int layerSize;
        private ActivatorInfo selectedActivator;


        public ObservableCollection<ActivatorInfo> AvailableActivators { get; }
        public int LayerSize { get => layerSize; set => SetProperty(ref layerSize, value); }
        public ActivatorInfo SelectedActivator { get => selectedActivator; set => SetProperty(ref selectedActivator, value); }
        public int LayerNb { get; }

        public HiddenLayerCharacteristicsViewModel(int layerNb)
        {
            var activatorService = new AvailableActivatorsService();
            AvailableActivators = new ObservableCollection<ActivatorInfo>(activatorService.GetActivators());
            SelectedActivator = AvailableActivators.First();
            LayerNb = layerNb;
            LayerSize = 1;
        }

        internal IndividualLayerConfiguration MakeConfiguration()
        {
            return new IndividualLayerConfiguration(LayerSize, SelectedActivator.Activator);
        }
    }
}
