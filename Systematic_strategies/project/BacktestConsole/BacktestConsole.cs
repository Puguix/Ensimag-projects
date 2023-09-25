/*
 * Main class
 * 
 * Use a JSON parameters input, a CSV data input
 * Output a CSV with the portfolio value
 * Save a figure to represent these graphically
 */

using PricingLibrary.DataClasses;
using PricingLibrary.MarketDataFeed;
using PricingLibrary.RebalancingOracleDescriptions;
using System.Reflection.Metadata.Ecma335;
using System.Runtime.InteropServices;

namespace ConsoleBacktest
{
    static class BacktestConsole
    {
        // BacktestConsole.exe <test-params> <mkt-data> <output-file>
        static void Main(string[] args)
        {
            // Verify if enough arguments are passed, or else exit with error
            if (args.Length < 3)
            {
                Console.WriteLine("Error command should be: BacktestConsole.exe <test-params> <mkt-data> <output-file>");
                Environment.Exit(1);
            }

            // Get parameters
            BasketTestParameters param = Reader.ReadParams(args[0]);

            // Create the strategy
            Strategy strat = new(param);

            // Initiate the portfolio
            Portfolio pf;

            //Initialise the first OutPutData
            OutputData dataFs;

            // Get data and convert it into a list of data feeds
            IEnumerable<ShareValue> data = Reader.ReadData(args[1]);
            List<DataFeed> df = data.GroupBy(d => d.DateOfPrice,
                      t => new { Symb = t.Id.Trim(), Val = t.Value },
                      (key, g) => new DataFeed(key, g.ToDictionary(e => e.Symb, e => e.Val))).ToList();

            // Create lists of output data
            List<OutputData> outputData = new();

            //First iteration
            (pf, dataFs) = strat.MakePf(df[0]);
            outputData.Add(dataFs);

            // Iterate over data
            int compteur = 0;
            foreach (DataFeed d in df.Skip(1))
            {
                if (strat.Rebalance(compteur, d))
                {
                    outputData.Add(strat.Compute(pf, d));
                    compteur = 0;
                }
                compteur += 1;
            }

            // Write output data into a JSON file
            Writer.WriteData(args[2], outputData);
        }
    }
}