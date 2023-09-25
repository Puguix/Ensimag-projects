/*
 * Class to read data from a CSV file OR to read input parameters from a a JSON
 */

using CsvHelper;
using PricingLibrary.DataClasses;
using PricingLibrary.MarketDataFeed;
using PricingLibrary.RebalancingOracleDescriptions;
using System.Globalization;
using System.Linq.Expressions;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace GrpcEvaluation
{
    static class Reader
    {
        // Function to get data from a CSV file from path
        public static IEnumerable<ShareValue> ReadData(string path)
        {
            var reader = new StreamReader(path);
            var csv = new CsvReader(reader, CultureInfo.InvariantCulture);
            return csv.GetRecords<ShareValue>();
        }

        // Function to get parameters from a JSON file
        public static BasketTestParameters ReadParams(string path)
        {
            var options = new JsonSerializerOptions()
            {
                PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
                Converters = { new JsonStringEnumConverter(), new RebalancingOracleDescriptionConverter() }
            };

            string JSON = File.ReadAllText(path);

            BasketTestParameters p = new();
            try
            {
                p = JsonSerializer.Deserialize<BasketTestParameters>(JSON, options);
            }
            catch (Exception ex)
            {
                Console.WriteLine(ex.Message);
                Environment.Exit(1);
            }
            return p;
        }
    }
}
