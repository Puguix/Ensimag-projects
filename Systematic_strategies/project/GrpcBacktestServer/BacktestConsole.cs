/*
 * Main class
 * 
 * Use a JSON parameters input, a CSV data input
 * Output a CSV with the portfolio value
 * Save a figure to represent these graphically
 */

using BacktestGrpc.Protos;
using Google.Protobuf.WellKnownTypes;
using PricingLibrary.DataClasses;
using PricingLibrary.MarketDataFeed;
using PricingLibrary.RebalancingOracleDescriptions;
using System.Reflection.Metadata.Ecma335;
using System.Runtime.InteropServices;

namespace GrpcServer
{
    static class BacktestConsole
    {
        // BacktestConsole.exe <test-params> <mkt-data> <output-file>
        public static BacktestOutput Compute(BacktestRequest request) //BasketTestParameters param, IEnumerable<ShareValue> data)
        {
            //convert request.tstparams in param
            BasketTestParameters param = ConvertParams(request.TstParams);

            // Create the strategy
            Strategy strat = new(param);

            // Initiate the portfolio
            Portfolio pf;

            //Initialise the first OutPutData
            BacktestInfo dataFs;

            // Get data and convert it into a list of data feeds
            List<DataFeed> df = request.Data.DataValues.GroupBy(d => d.Date.ToDateTime(),
                      t => new { Symb = t.Id, Val = t.Value },
                      (key, g) => new DataFeed(key, g.ToDictionary(e => e.Symb, e => e.Val))).ToList();

            // Create lists of output data
            BacktestOutput outputBacktest = new();
        
            //First iteration
            (pf, dataFs) = strat.MakePf(df[0]);
            outputBacktest.BacktestInfo.Add(dataFs);

            // Iterate over data
            int compteur = 0;
            foreach (DataFeed d in df.Skip(1))
            {
                if (strat.Rebalance(compteur, d)) {
                    outputBacktest.BacktestInfo.Add(strat.Compute(pf, d));
                    compteur = 0;
                }
                compteur+=1;
            }
            return outputBacktest;
        }

        // Function to convert test parameters from the proto class to the c# class
        private static BasketTestParameters ConvertParams(TestParams TstParams)
        {
            BasketTestParameters param = new();

            //Convert the Basket Pricing Parameters
            BasketPricingParameters pricingParam = new() { Volatilities = new double[TstParams.PriceParams.Corrs.Count] };
            double[][] cor = new double[TstParams.PriceParams.Corrs.Count][];
            for (int i = 0; i < TstParams.PriceParams.Corrs.Count; i++)
            {
                double[] c = new double[TstParams.PriceParams.Corrs.Count];
                pricingParam.Volatilities[i] = TstParams.PriceParams.Vols[i];
                for (int j = 0; j < TstParams.PriceParams.Corrs[i].Value.Count; j++)
                {
                    c[j] = TstParams.PriceParams.Corrs[i].Value[j];
                }
                cor[i] = c;
            }
            pricingParam.Correlations = cor;
            param.PricingParams = pricingParam;

            //convert the rebalancing oracle
            IRebalancingOracleDescription oracle;
            if (TstParams.RebParams.RebTypeCase == RebalancingParams.RebTypeOneofCase.Regular)
            {
                RegularOracleDescription regular = new()
                {
                    Period = TstParams.RebParams.Regular.Period
                };
                oracle = regular;
            }
            else
            {
                WeeklyOracleDescription weekly = new()
                {
                    RebalancingDay = (DayOfWeek)TstParams.RebParams.Weekly.Day
                };
                oracle = weekly;
            }
            param.RebalancingOracleDescription = oracle;

            //convert the Basket
            Basket option = new()
            {
                Strike = TstParams.BasketParams.Strike,
                Maturity = TstParams.BasketParams.Maturity.ToDateTime()
            };
            string[] ids = new string[TstParams.BasketParams.Weights.Count];
            double[] weights = new double[TstParams.BasketParams.Weights.Count];
            for (int j = 0; j < TstParams.BasketParams.ShareIds.Count; j++)
            {
                ids[j] = TstParams.BasketParams.ShareIds[j];
                weights[j] = TstParams.BasketParams.Weights[j];
            }
            option.Weights = weights;
            option.UnderlyingShareIds = ids;
            param.BasketOption = option;

            return param;
        }
    }
}
