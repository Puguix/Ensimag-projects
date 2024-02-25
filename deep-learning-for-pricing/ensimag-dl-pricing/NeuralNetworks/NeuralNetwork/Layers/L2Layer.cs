using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common.Activators;
using NeuralNetwork.Common.Layers;
using NeuralNetwork.Common.Serialization;
using System;
using System.ComponentModel;
using NeuralNetwork.Common.GradientAdjustmentParameters;
using NeuralNetwork.GradientAlgorithms;
using NeuralNetwork.Gradients;

namespace NeuralNetwork.Layers
{
    internal class L2Layer : ILayerWithWeights
    {
        public ILayerWithWeights UnderlyingLayer { get; set; }
        public double K { get; set; }

        public int LayerSize { get; }

        public int InputSize { get; }
        private int batchSize;
        public int BatchSize
        {
            get { return batchSize; }
            set
            {
                batchSize = value;
                UnderlyingLayer.BatchSize = batchSize;
                Activation = Matrix<double>.Build.Dense(LayerSize, batchSize);
            }
        }

        public Matrix<double> Activation { get; set; }
        public Matrix<double> WeightedError { get; set; }
        public Matrix<double> Weights { get; set; }
        public L2Layer(ILayerWithWeights layer, int batchSize, double k)
        {
            UnderlyingLayer = layer;
            K = k;
            LayerSize = layer.LayerSize;
            InputSize = layer.InputSize;
            this.batchSize = batchSize;
            Activation = layer.Activation;
            WeightedError = layer.WeightedError;
            Weights = layer.Weights;
        }

        public void Propagate(Matrix<double> input)
        {
            UnderlyingLayer.Propagate(input);
            Activation = UnderlyingLayer.Activation;
        }

        public void BackPropagate(Matrix<double> upstreamWeightedErrors)
        {
            UnderlyingLayer.BackPropagate(upstreamWeightedErrors);
            Matrix<double> KTimesWeights = UnderlyingLayer.Weights.Multiply(K).Multiply(Matrix<double>.Build.Dense(UnderlyingLayer.Weights.ColumnCount, batchSize, 1));
            this.WeightedError = UnderlyingLayer.WeightedError.Add(KTimesWeights);
        }

        public void UpdateParameters()
        {
            UnderlyingLayer.UpdateParameters();
            this.Weights = UnderlyingLayer.Weights;
        }

        public bool Equals(ILayer other)
        {
            if (other.GetType() != this.GetType()) return false;
            if (InputSize != other.InputSize) return false;
            if (LayerSize != other.InputSize) return false;
            if (BatchSize != other.BatchSize) return false;
            if (Activation != other.Activation) return false;
            if (WeightedError != other.WeightedError) return false;
            L2Layer otherL2 = (L2Layer) other;
            if (otherL2.K != K) return false;
            if (otherL2.UnderlyingLayer != this.UnderlyingLayer) return false;
            return true;
    }
}
}