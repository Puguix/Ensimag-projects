using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common;

namespace DataProviders
{
    public class AndDataProvider : IDataProvider
    {
        public SplitData GetData()
        {
            var inputs = new double[2, 4] { { 0, 0, 1, 1 }, { 0, 1, 1, 0 } };
            var mathInputs = Matrix<double>.Build.DenseOfArray(inputs);
            var outputs = new double[1, 4] { { 0, 0, 1, 0 } };
            var mathOutputs = Matrix<double>.Build.DenseOfArray(outputs);
            var data = new MathData(mathInputs, mathOutputs);
            return new SplitData(data, data, data);
        }
    }
}