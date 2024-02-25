using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common.Activators;
using NeuralNetwork.Common.Layers;
using NeuralNetwork.Common.Serialization;
using System;
using System.ComponentModel;
using NeuralNetwork.Common.GradientAdjustmentParameters;
using NeuralNetwork.GradientAlgorithms;
using NeuralNetwork.Gradients;
using System.Xml.Linq;

namespace NeuralNetwork.Layers
{
    internal class StandardLayer : ILayerWithWeights
    {
        public int InputSize { get; }
        public int LayerSize { get; }
        public IActivator Activator { get; }
        private int batchSize;
        public int BatchSize {
            get { return batchSize; }
            set { 
                batchSize = value;
                Activation = Matrix<double>.Build.Dense(LayerSize, batchSize);
                NetInput = Matrix<double>.Build.Dense(InputSize, BatchSize);
            }
        }

        public Matrix<double> Bias { get; set; }
        public Matrix<double> Activation { get; set; }
        public Matrix<double> NetInput { get; set; }
        public Matrix<double> Input { get; set; }

        public Matrix<double> Error { get; set; }


        public IGradientAlgo GradientAlgorithm;
        public IGradientAdjustmentParameters GradParameters;

        public Matrix<double> Weights { get; set;  }
        public Matrix<double> WeightedError { get; set; }

        public StandardLayer(Matrix<double> initialWeights, Matrix<double> initialBias, int batchSize, IActivator activator, IGradientAdjustmentParameters gradParameters)
        {
            LayerSize = initialWeights.ColumnCount;
            InputSize = initialWeights.RowCount;
            this.batchSize = batchSize;
            Weights = initialWeights;
            Bias = initialBias;
            Activator = activator ?? throw new ArgumentNullException(nameof(activator));
            Activation = Matrix<double>.Build.Dense(LayerSize, BatchSize);
            Error = Matrix<double>.Build.Dense(LayerSize, batchSize);
            WeightedError = Matrix<double>.Build.Dense(batchSize, LayerSize);
            GradParameters = gradParameters;
            GradientAlgorithm = GradientAlgoFactory.Build(gradParameters, Weights, Bias);
            NetInput = Matrix<double>.Build.Dense(InputSize, BatchSize);
            Input = Matrix<double>.Build.Dense(InputSize, BatchSize);
        }

        public void Propagate(Matrix<double> input)
        {
            //Matrix<double> inter = Weights.TransposeAndMultiply(input);
            Input = input;
            //Matrix<double> inter = input.Multiply(Matrix<double>.Build.Dense(input.ColumnCount, BatchSize,  1));
            NetInput = Weights.TransposeThisAndMultiply(input).Add(Bias.Multiply(Matrix<double>.Build.Dense(1, input.ColumnCount, 1)));
            Activation = NetInput;
            NetInput.Map(Activator.Apply, Activation);
        }

        public void BackPropagate(Matrix<double> upstreamWeightedErrors)
        {
            Error = NetInput.Map(Activator.ApplyDerivative).PointwiseMultiply(upstreamWeightedErrors);
            WeightedError = Weights.Multiply(Error);
        }

        public void UpdateParameters()
        {
            Matrix<double> gradWeight = Input.TransposeAndMultiply(Error).Divide(BatchSize);
            Matrix<double> gradBias = Error.Multiply(Matrix<double>.Build.Dense(BatchSize,1,1)).Divide(BatchSize);

            // Mise à jour des paramètres
            Matrix<double> inter = GradientAlgorithm.UpdateWeightGrad(gradWeight);
            Weights = Weights.Add(inter);
            Bias = Bias.Add(GradientAlgorithm.UpdateBiasGrad(gradBias));
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