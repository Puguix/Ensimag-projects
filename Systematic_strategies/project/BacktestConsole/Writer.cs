/*
 * Class to write the data in an output JSON file
 */

using PricingLibrary.DataClasses;
using PricingLibrary.RebalancingOracleDescriptions;
using System.Globalization;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace ConsoleBacktest
{
    static class Writer
    {
        // Write the list of output data values to the JSON file passed in *path*
        public static void WriteData(string path, List<OutputData> dataValues)
        {
            var options = new JsonSerializerOptions()
            {
                WriteIndented = true,
                PropertyNamingPolicy = JsonNamingPolicy.CamelCase,
                Converters = { new JsonStringEnumConverter(), new RebalancingOracleDescriptionConverter() }
            };

            string jsonString = JsonSerializer.Serialize(dataValues, options);
            File.WriteAllText(path, jsonString);
        }
    }
}