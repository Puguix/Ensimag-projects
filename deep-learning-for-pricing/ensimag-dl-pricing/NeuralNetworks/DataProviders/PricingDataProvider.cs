using DataProviders.Properties;
using MathNet.Numerics.LinearAlgebra.Double;
using NeuralNetwork.Common;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;

namespace DataProviders
{
    public class PricingDataProvider : IDataProvider
    {
        public SplitData GetData()
        {
            var inputData = Resources.pricing_data_inputs;
            var outputData = Resources.pricing_data_outputs;
            var result = ConvertToSplitData(inputData, outputData);
            return result;
        }

        private IEnumerable<double[]> ReadToCsv(string dataString)
        {
            CultureInfo customCulture = (CultureInfo)System.Threading.Thread.CurrentThread.CurrentCulture.Clone();
            customCulture.NumberFormat.NumberDecimalSeparator = ".";
            System.Threading.Thread.CurrentThread.CurrentCulture = customCulture;
            using (StringReader sr = new StringReader(dataString))
            {
                string line;
                while ((line = sr.ReadLine()) != null)
                {
                    double[] arr = line.Split(',').Select(double.Parse).ToArray();
                    yield return arr;
                }
            }
        }

        private SplitData ConvertToSplitData(string inputPath, string outputPath)
        {
            var input = ReadToCsv(inputPath);
            var inputMatrix = DenseMatrix.OfColumnArrays(input);
            var output = ReadToCsv(outputPath);
            var outputMatrix = DenseMatrix.OfColumnArrays(output);
            var inputSize = inputMatrix.RowCount;
            var outputSize = outputMatrix.RowCount;
            var dataSize = inputMatrix.ColumnCount;
            var trainingSize = 3 * dataSize / 5;
            var validationSize = dataSize / 5;
            var trainingInputs = inputMatrix.SubMatrix(0, inputSize, 0, trainingSize);
            var trainingOutputs = outputMatrix.SubMatrix(0, outputSize, 0, trainingSize);
            var training = new MathData(trainingInputs, trainingOutputs);
            var validationInputs = inputMatrix.SubMatrix(0, inputSize, trainingSize, validationSize);
            var validationOutputs = outputMatrix.SubMatrix(0, outputSize, trainingSize, validationSize);
            var validation = new MathData(validationInputs, validationOutputs);
            var testingInputs = inputMatrix.SubMatrix(0, inputSize, trainingSize + validationSize, dataSize - (trainingSize + validationSize));
            var testingOutputs = outputMatrix.SubMatrix(0, outputSize, trainingSize + validationSize, dataSize - (trainingSize + validationSize));
            var testing = new MathData(testingInputs, testingOutputs);
            return new SplitData(training, validation, testing);
        }
    }
}