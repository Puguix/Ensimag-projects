/*
 * Class to describe a portfolio
 */

using PricingLibrary.Computations;
using PricingLibrary.DataClasses;
using PricingLibrary.MarketDataFeed;
using PricingLibrary.TimeHandler;
using System.Diagnostics;

namespace GrpcServer
{
    class Portfolio
    {
        public Dictionary<string, double> Composition { get;private set; }
    
        public double Value { get;private set; }
        public DateTime Date {  get; set; } 


        public Portfolio()
        {
            Composition = new Dictionary<string, double>();
        }

        // Function to update the composition of the portfolio
        public void UpdateCompo(string[] share, double[] compo)
        {
            Composition.Clear();
            for (int i = 0; i < compo.Length; i++)
            {
                Composition.Add(share[i], compo[i]);
            }
        }

        // Function to compute the value of the portfolio
        public void UpdateValue(DataFeed d)
        {
            Value = 0;
            foreach (string share in d.PriceList.Keys)
            {
                Value += Composition[share] * d.PriceList[share];
            }
            Value += Composition["RiskFree"] * RiskFreeRateProvider.GetRiskFreeRateAccruedValue(Date, d.Date);
        }
    }   
}
