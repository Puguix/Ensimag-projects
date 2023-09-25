/*
 * Class configuring and running the client
 */

using System.Threading.Tasks;
using Grpc.Net.Client;
using BacktestGrpc.Protos;
using PricingLibrary.DataClasses;
using static System.Runtime.InteropServices.JavaScript.JSType;
using Google.Protobuf.WellKnownTypes;
using PricingLibrary.RebalancingOracleDescriptions;
using PricingLibrary.MarketDataFeed;

namespace GrpcEvaluation
{
    static class Program { 
        public static async Task Main(string[] args)
        {
            // Connect the client to the server
            using var channel = GrpcChannel.ForAddress("https://localhost:7177");
            var client = new BacktestRunner.BacktestRunnerClient(channel);

            // Read the parameters
            BasketTestParameters btp = Reader.ReadParams(args[0]);

            // Read the data
            IEnumerable<ShareValue> shareValues = Reader.ReadData(args[1]);

            // Request
            BacktestRequest request = ConvertParams(btp, shareValues);

            // Send the request and wait for the reply
            BacktestOutput reply = await client.RunBacktestAsync(request);

            // Convert the response
            List<OutputData> dataValues = new();
            foreach (BacktestInfo info in reply.BacktestInfo)
            {
                OutputData data = new() { Date = info.Date.ToDateTime(), Price = info.Price, Value = info.PortfolioValue, PriceStdDev = info.PriceStddev};
                List<double> deltas = new();
                List<double> deltaStd = new();
                for (int i = 0; i < info.Delta.Count; i++)
                {
                    deltas.Add(info.Delta[i]);
                    deltaStd.Add(info.DeltaStddev[i]);
                }
                data.Deltas = deltas.ToArray();
                data.DeltasStdDev = deltaStd.ToArray();
                dataValues.Add(data);
            }

            // Write the response
            Writer.WriteData(args[2], dataValues);
        }

        // Function to convert parameters instance to proto from c#
        private static BacktestRequest ConvertParams(BasketTestParameters btp, IEnumerable<ShareValue> data)
        {
            // Basket parameters
            BasketParams basketParams = new() { Strike = btp.BasketOption.Strike, Maturity = DateTime.SpecifyKind(btp.BasketOption.Maturity, DateTimeKind.Utc).ToTimestamp() };
            for (int i = 0; i < btp.BasketOption.Weights.Length; i++)
            {
                basketParams.ShareIds.Add(btp.BasketOption.UnderlyingShareIds[i]);
                basketParams.Weights.Add(btp.BasketOption.Weights[i]);
            }

            // Rebalancing parameters
            RebalancingParams rebalancingParams;
            if (btp.RebalancingOracleDescription.Type == RebalancingOracleType.Regular)
            {
                RegularOracleDescription reg = (RegularOracleDescription)btp.RebalancingOracleDescription;
                RegularRebalancing regParams = new() { Period = reg.Period };
                rebalancingParams = new() { Regular = regParams };
            }
            else
            {
                WeeklyOracleDescription weekly = (WeeklyOracleDescription)btp.RebalancingOracleDescription;
                WeeklyRebalancing weeklyParams = new() { Day = (ProtoDayOfWeek)weekly.RebalancingDay };
                rebalancingParams = new() { Weekly = weeklyParams };
            }

            // Pricing parameters
            PricingParams pricingParams = new();
            for (int i = 0; i < btp.PricingParams.Correlations.Length; i++)
            {
                CorrLine cor = new();
                for (int j = 0; j < btp.PricingParams.Correlations.Length; j++)
                {
                    cor.Value.Add(btp.PricingParams.Correlations[j]);
                }
                pricingParams.Corrs.Add(cor);
                pricingParams.Vols.Add(btp.PricingParams.Volatilities[i]);
            }

            // Test parameters
            TestParams testParams = new() { BasketParams = basketParams, PriceParams = pricingParams, RebParams = rebalancingParams };

            // Data parameters
            DataParams dataParams = new();
            foreach (ShareValue v in data)
            {
                ShareData shareData = new() { Value = v.Value, Date = DateTime.SpecifyKind(v.DateOfPrice, DateTimeKind.Utc).ToTimestamp(), Id = v.Id };
                dataParams.DataValues.Add(shareData);
            }

            return new() { Data = dataParams, TstParams = testParams };
        }
    }
}