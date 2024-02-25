using System;
using System.Collections.Generic;
using System.Text;

namespace DataProviders
{
    public static class DataProviderConverter
    {
        public static IDataProvider Convert(DataProviderType providerType)
        {
            switch (providerType)
            {
                case DataProviderType.AndData:
                    return new AndDataProvider();
                case DataProviderType.XorData:
                    return new XorDataProvider();
                case DataProviderType.PricingData:
                    return new PricingDataProvider();
                default:
                    throw new InvalidOperationException("Unknown data provider type");
            }
        }
    }
}
