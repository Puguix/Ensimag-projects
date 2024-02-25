using MathNet.Numerics.LinearAlgebra;
using MathNet.Numerics.LinearAlgebra.Double;
using NeuralNetwork.Common;
using NeuralNetwork.Common.JsonUtils;
using NeuralNetwork.Common.Serialization;
using NeuralNetwork.Serialization;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text.Json;

namespace PropagationComparison
{
    internal static class Program
    {
        static void Main(string[] args)
        {
            var serializedNetworkPath = args[0];
            var serializedNetwork = JsonIO.DeserializeNetworkFromFile(serializedNetworkPath);
            var network = NetworkDeserializer.Deserialize(serializedNetwork);
            var inputRoot = args[1];
            var gradientRoot = args[2];
            int repeats;
            if (args.Length == 5)
            {
                var repeatRoot = args[4];
                repeats = (int)ReadCsv(repeatRoot).ToList()[0][0];
            }
            else repeats = 1;
            var data = GetMathData(inputRoot, gradientRoot);
            var dataSize = data.Inputs.ColumnCount;
            network.BatchSize = dataSize;

            network.Propagate(data.Inputs);
            double[] firstPropagation = ConvertToArray(network.Output);
            for (int i = 1; i < repeats; i++)
            {
                network.Learn(data.Outputs);
                network.Propagate(data.Inputs);
            }
            network.Learn(data.Outputs);
            network.Propagate(data.Inputs);
            double[] secondPropagation = ConvertToArray(network.Output);
            var summary = new OutputSummary(firstPropagation, secondPropagation);
            WriteJson(args, summary);
        }

        private static void WriteJson(string[] args, OutputSummary summary)
        {
            if (args.Length < 4)
            {
                WriteToConsole(summary);
            }
            else
            {
                var outputFile = args[3];
                WriteToFile(summary, outputFile);
            }
        }

        private static string WriteJson(OutputSummary summary)
        {
            var options = new JsonSerializerOptions { WriteIndented = true };
            var output = JsonSerializer.Serialize(summary, options);
            return output;
        }

        private static void WriteToConsole(OutputSummary summary)
        {
            var output = WriteJson(summary);
            Console.WriteLine(output);
        }

        private static void WriteToFile(OutputSummary summary, string outputFile)
        {
            var output = WriteJson(summary);
            File.WriteAllText(outputFile, output);            
        }
        private static double[] ConvertToArray(Matrix<double> output)
        {
            return output.ToRowArrays()[0];
        }

        private static MathData GetMathData(string dataRoot, string gradientEoot)
        {
            var input = ReadCsv(dataRoot);
            var inputMatrix = DenseMatrix.OfColumnArrays(input);
            var output = ReadCsv(gradientEoot);
            var outputMatrix = DenseMatrix.OfColumnArrays(output);
            var result = new MathData(inputMatrix, outputMatrix);
            return result;
        }

        private static IEnumerable<double[]> ReadCsv(string filePath)
        {
            CultureInfo customCulture = (CultureInfo)System.Threading.Thread.CurrentThread.CurrentCulture.Clone();
            customCulture.NumberFormat.NumberDecimalSeparator = ".";
            System.Threading.Thread.CurrentThread.CurrentCulture = customCulture;
            using (StreamReader sr = new StreamReader(filePath))
            {
                string line;
                while ((line = sr.ReadLine()) != null)
                {
                    double[] arr = line.Split(',').Select(double.Parse).ToArray();
                    yield return arr;
                }
            }
        }
    }
}
