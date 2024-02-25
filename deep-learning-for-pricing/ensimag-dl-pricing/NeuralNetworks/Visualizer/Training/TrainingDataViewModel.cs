using Prism.Mvvm;
using System.Collections.ObjectModel;
using System.Linq;
using Visualizer.Services;

namespace Visualizer.Training
{
    internal class TrainingDataViewModel : BindableBase
    {
        private DataProviderInfo selectedDataProvider;
        private DataShufflerInfo selectedShuffler;

        public ObservableCollection<DataShufflerInfo> AvailableDataShufflers { get; }

        public DataShufflerInfo SelectedShuffler
        {
            get => selectedShuffler;
            set => SetProperty(ref selectedShuffler, value);
        }

        public ObservableCollection<DataProviderInfo> AvailableDataProviders { get; }

        public DataProviderInfo SelectedDataProvider
        {
            get => selectedDataProvider;
            set => SetProperty(ref selectedDataProvider, value);
        }

        public TrainingDataViewModel()
        {
            var providerServices = new AvailableDataProvidersService();
            AvailableDataProviders = new ObservableCollection<DataProviderInfo>(providerServices.GetDataProviders());
            var shufflerService = new AvailableDataShufflersService();
            AvailableDataShufflers = new ObservableCollection<DataShufflerInfo>(shufflerService.GetDataShufflers());
            SelectedDataProvider = AvailableDataProviders.First();
            SelectedShuffler = AvailableDataShufflers.First();
        }
    }
}