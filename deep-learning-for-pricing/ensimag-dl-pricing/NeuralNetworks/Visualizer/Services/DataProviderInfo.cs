using DataProviders;

namespace Visualizer.Services
{
    internal class DataProviderInfo
    {
        public DataProviderInfo(string name, IDataProvider dataProvider)
        {
            Name = name;
            DataProvider = dataProvider;
        }

        public string Name { get; }
        public IDataProvider DataProvider { get; }
    }
}