/*
 * Class to apply the strategy to a portfolio given market data and parameters
 */

using BacktestGrpc.Protos;
using Google.Protobuf.WellKnownTypes;
using Microsoft.VisualBasic;
using PricingLibrary.Computations;
using PricingLibrary.DataClasses;
using PricingLibrary.MarketDataFeed;
using PricingLibrary.RebalancingOracleDescriptions;
using PricingLibrary.TimeHandler;
using System.Linq;
using System.Runtime.InteropServices;
using static System.Runtime.InteropServices.JavaScript.JSType;

namespace GrpcServer
{
    class Strategy
    {
        private BacktestInfo Data { set; get; }
        private BasketTestParameters Parameters { set; get; }
        private PricingResults Prices { set; get; }
        private Pricer Pricer { set; get; }
        private double PortfolioValue { get; set; }
        private double SpotValue { get; set; }
        private double TimeToMaturity { get; set; }
        private double[]? Spots { get; set; }


        public Strategy(BasketTestParameters param)
        {
            Data = new BacktestInfo();
            Pricer = new Pricer(param);
            Parameters = param;
        }

        // Function to update the data
        private void Update(DataFeed d)
        {
            // Reset attributes
            PortfolioValue = 0;
            SpotValue = 0;
            Data = new();
            TimeToMaturity = MathDateConverter.ConvertToMathDistance(d.Date, Parameters.BasketOption.Maturity);
            Spots = new double[d.PriceList.Count];

            // For each share, update the market value
            for (int i = 0; i < d.PriceList.Count; i++)
            {
                KeyValuePair<string, double> v = d.PriceList.ElementAt(i);
                Spots[i] = v.Value;
            }

            // Compute the new prices et deltas
            Prices = Pricer.Price(TimeToMaturity, Spots);

            // Calculate the total spot value after redistribution
            for (int i = 0; i < d.PriceList.Count; i++)
            {
                SpotValue += Prices.Deltas[i] * Spots[i];
            }
        }

        // Function to update the parameters, and rebalance the composition of the portfolio
        public BacktestInfo Compute(Portfolio pf, DataFeed d)
        {
            // Update all attributes and market values, then compute the prices
            Update(d);

            // Update the pf composition
            pf.UpdateValue(d);
            double[] rfValue = new double[] { pf.Value - SpotValue };
            pf.UpdateCompo(d.PriceList.Keys.Concat(new string[] { "RiskFree" }).ToArray(), Prices.Deltas.Concat(rfValue).ToArray());

            // Update the date of the last update
            pf.Date = d.Date;

            // Update output data
            for (int i = 0; i < Prices.Deltas.Length; i++)
            {
                Data.Delta.Add(Prices.Deltas[i]);
                Data.DeltaStddev.Add(Prices.DeltaStdDev[i]);
            }
            Data.Price = Prices.Price;
            Data.PriceStddev = Prices.PriceStdDev;
            Data.Date = DateTime.SpecifyKind(d.Date, DateTimeKind.Utc).ToTimestamp();
            Data.PortfolioValue = pf.Value;
            return Data;
        }

        // Function to make the first composition of the portfolio
        public (Portfolio, BacktestInfo) MakePf(DataFeed d)
        {
            Update(d);

            // Compute the portfolio value
            PortfolioValue = Prices.Price;

            // Create the portfolio
            Portfolio pf = new()
            {
                Date = d.Date
            };
            double[] rfValue = new double[] { PortfolioValue - SpotValue };
            pf.UpdateCompo(d.PriceList.Keys.Concat(new string[] { "RiskFree" }).ToArray(), Prices.Deltas.Concat(rfValue).ToArray());
            pf.UpdateValue(d);

            // Update output data
            for (int i = 0; i < Prices.Deltas.Length; i++)
            {
                Data.Delta.Add(Prices.Deltas[i]);
                Data.DeltaStddev.Add(Prices.DeltaStdDev[i]);
            }
            Data.Price = Prices.Price;
            Data.PriceStddev = Prices.PriceStdDev;
            Data.Date = DateTime.SpecifyKind(d.Date, DateTimeKind.Utc).ToTimestamp();
            Data.PortfolioValue = pf.Value;

            return (pf, Data);
        }

        // Function to check if the portfolio needs to be rebalanced
        public bool Rebalance(int compteur, DataFeed d)
        {
            // Case: daily rebalancing
            if (Parameters.RebalancingOracleDescription.Type == PricingLibrary.RebalancingOracleDescriptions.RebalancingOracleType.Regular)
            {
                IRebalancingOracleDescription rebalancingOracleDescription = Parameters.RebalancingOracleDescription;
                RegularOracleDescription regular = (RegularOracleDescription)rebalancingOracleDescription;
                return compteur % regular.Period == 0;
            }
            // Case: weekly rebalancing
            else
            {
                IRebalancingOracleDescription rebalancingOracleDescription = Parameters.RebalancingOracleDescription;
                WeeklyOracleDescription weekly = (WeeklyOracleDescription)rebalancingOracleDescription;
                return d.Date.DayOfWeek == weekly.RebalancingDay;
            }
        }
    }
}
