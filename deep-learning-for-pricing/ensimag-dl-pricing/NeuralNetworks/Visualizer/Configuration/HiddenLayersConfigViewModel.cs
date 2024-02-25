using Prism.Mvvm;
using System;
using System.Collections.ObjectModel;

namespace Visualizer.Configuration
{
    class HiddenLayersConfigViewModel : BindableBase
    {
        private int hiddenLayerNb;
        private ObservableCollection<HiddenLayerCharacteristicsViewModel> characteristics;

        public int HiddenLayerNb
        {
            get => hiddenLayerNb;
            set
            {
                SetProperty(ref hiddenLayerNb, value);
                Characteristics = Initialize(HiddenLayerNb);
            }
        }

        public ObservableCollection<HiddenLayerCharacteristicsViewModel> Characteristics
        {
            get => characteristics;
            private set => SetProperty(ref characteristics, value);
        }

        public HiddenLayersConfigViewModel()
        {
            HiddenLayerNb = 1;
            Characteristics = Initialize(HiddenLayerNb);
        }

        private ObservableCollection<HiddenLayerCharacteristicsViewModel> Initialize(int hiddenLayernb)
        {
            var result = new HiddenLayerCharacteristicsViewModel[HiddenLayerNb];
            for (int i = 0; i < hiddenLayernb; i++)
            {
                result[i] = new HiddenLayerCharacteristicsViewModel(i+1);
            }
            return new ObservableCollection<HiddenLayerCharacteristicsViewModel>(result);
        }
    }
}
