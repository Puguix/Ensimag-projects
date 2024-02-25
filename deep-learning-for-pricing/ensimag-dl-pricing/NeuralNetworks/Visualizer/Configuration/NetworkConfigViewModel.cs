using NeuralNetwork.Activators;
using NeuralNetwork.GradientAccelerators;
using NeuralNetwork.Structure.Configurations;
using Prism.Commands;
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
    class NetworkConfigViewModel : BindableBase
    {
        //private string hiddenLayerCharacteristics;
        private ActivatorInfo selectedOutputActivator;
        private double weightDecayFactor;
        public HiddenLayersConfigViewModel HiddenLayers { get; }

        public ObservableCollection<ActivatorInfo> AvailableOutputActivators { get; }
        
        //public string HiddenLayerCharacteristics
        //{
        //    get => hiddenLayerCharacteristics;
        //    set => SetProperty(ref hiddenLayerCharacteristics, value);
        //}
        public ActivatorInfo SelectedOutputActivator
        {
            get => selectedOutputActivator;
            set => SetProperty(ref selectedOutputActivator, value);
        }


        public double WeightDecayFactor
        {
            get => weightDecayFactor;
            set => SetProperty(ref weightDecayFactor, value);
        }
        
        public NetworkConfigViewModel()
        {
            var activatorService = new AvailableActivatorsService();
            AvailableOutputActivators = new ObservableCollection<ActivatorInfo>(activatorService.GetActivators());
            SelectedOutputActivator = AvailableOutputActivators.First();
            HiddenLayers = new HiddenLayersConfigViewModel();
            weightDecayFactor = 0;
            //HiddenLayerCharacteristics = "1";
        }

        //public int[] GetHiddenLayerCharacteristics()
        //{
        //    //var hiddenLayers = HiddenLayerCharacteristics.Split(',').Select(int.Parse).ToArray();
        //    return null;
        //}

        public IndividualLayerConfiguration[] GetIndividualLayerConfigurations(int outputSize)
        {
            var hiddenLayerNb = HiddenLayers.HiddenLayerNb;
            IndividualLayerConfiguration[] result = new IndividualLayerConfiguration[hiddenLayerNb + 1];
            for (int i = 0; i < hiddenLayerNb; i++)
            {
                result[i] = HiddenLayers.Characteristics[i].MakeConfiguration();
            }
            result[hiddenLayerNb] = new IndividualLayerConfiguration(outputSize, SelectedOutputActivator.Activator);
            return result;
        }


        //public ActivatorType GetActivator()
        //{
        //    return SelectedOutputActivator.Activator;
        //}

        
    }
}
