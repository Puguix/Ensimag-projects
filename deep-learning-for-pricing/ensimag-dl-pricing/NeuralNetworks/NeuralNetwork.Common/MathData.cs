using MathNet.Numerics.LinearAlgebra;

namespace NeuralNetwork.Common
{
    /// <summary>
    /// Class designed to store the inputs and outputs used to train or evaluate a network.
    /// </summary>
    public class MathData
    {
        public MathData(Matrix<double> inputs, Matrix<double> outputs)
        {
            Inputs = inputs;
            Outputs = outputs;
        }

        public Matrix<double> Inputs { get; }
        public Matrix<double> Outputs { get; }
    }
}