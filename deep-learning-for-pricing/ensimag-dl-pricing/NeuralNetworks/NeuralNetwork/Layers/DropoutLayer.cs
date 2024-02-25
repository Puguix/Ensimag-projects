using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common.Layers;
using MathNet.Numerics.Distributions;

namespace NeuralNetwork.Layers
{
    internal class DropoutLayer : ILayer
    {
        public int LayerSize { get; }
        public int InputSize { get; }

        private int batchSize;
        public int BatchSize
        {
            get { return batchSize; }
            set
            {
                batchSize = value;
                Activation = Matrix<double>.Build.Dense(LayerSize, batchSize);
            }
        }

        public Matrix<double> Activation { get; set; }
        public Matrix<double> WeightedError { get; set; }
        public Matrix<double> Mask { get; set; }
        public double KeepProbability { get; set; }
        public double InitialKeepProbability { get; }


        public DropoutLayer(int layerSize, double keepProbability, int batchSize)
        {
            LayerSize = layerSize;
            BatchSize = batchSize;
            Activation = Matrix<double>.Build.Dense(LayerSize, BatchSize);
            InitialKeepProbability = keepProbability;
            KeepProbability = InitialKeepProbability;
            Mask = Matrix<double>.Build.Dense(LayerSize, 1);
        }


        public void Propagate(Matrix<double> input)
        {
            Mask = Matrix<double>.Build.Random(LayerSize, 1, new ContinuousUniform(0, 1));
            Mask.MapInplace(x => x > KeepProbability ? 0.0 : 1.0);
            Activation = input.PointwiseMultiply(Mask.Multiply(Matrix<double>.Build.Dense(1, input.ColumnCount, 1)));
        }

        public void BackPropagate(Matrix<double> upstreamWeightedErrors)
        {
            WeightedError = upstreamWeightedErrors;
        }

        public void UpdateParameters() 
        {
        }

        public bool Equals(ILayer other)
        {
            if (other.GetType() != this.GetType()) return false;
            if (InputSize != other.InputSize) return false;
            if (LayerSize != other.InputSize) return false;
            if (BatchSize != other.BatchSize) return false;
            if (Activation != other.Activation) return false;
            if (WeightedError != other.WeightedError) return false;
            return true;
        }

    }

}