using DataProviders;
using System.Collections.Generic;

namespace Visualizer.Services
{
    internal class AvailableDataProvidersService
    {
        public List<DataProviderInfo> GetDataProviders()
        {
            return new List<DataProviderInfo>
            {
                new DataProviderInfo("Xor", new XorDataProvider()),
                new DataProviderInfo("And", new AndDataProvider()),
                new DataProviderInfo("Pricing", new PricingDataProvider())
            };
        }
    }
}