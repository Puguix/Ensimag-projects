using DataProviders;
using NeuralNetwork.Common;
using NeuralNetwork.Common.JsonUtils;
using NeuralNetwork.Common.Serialization;
using NeuralNetwork.Serialization;
using RegressionTester;
using System;
using System.IO;
using System.Text.Json;

namespace RegressionConsole
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length == 0 || args.Length > 2)
            {
                throw new InvalidOperationException("1 or 2 arguments");
            }
            var serializedNetworkFile = args[0]; 
            var network = LoadNetwork(serializedNetworkFile);
            var tester = new Evaluator(network, new RelativeDifference());
            var testData = LoadData();
            var result = tester.Test(testData);
            var summary = new StatisticsSummary(result);
            if (args.Length < 2)
            {
                WriteToConsole(summary);
            }
            else
            {
                var outputFile = args[1];
                WriteToFile(summary, outputFile);
            }
        }

        private static void WriteToConsole(StatisticsSummary summary)
        {
            var output = JsonSerializer.Serialize(summary);
            Console.WriteLine(output);
        }

        private static void WriteToFile(StatisticsSummary summary, string outputFile)
        {
            var output = JsonSerializer.Serialize(summary);
            File.WriteAllText(outputFile, output);
        }

        private static INetwork LoadNetwork(string serializedNetworkFile)
        {
            var serializedNetwork = JsonIO.DeserializeNetworkFromFile(serializedNetworkFile);
            return NetworkDeserializer.Deserialize(serializedNetwork);
        }

        private static MathData LoadData()
        {
            var bsProvider = new PricingDataProvider();
            var splitData = bsProvider.GetData();
            return splitData.TestData;
        }
    }
}
