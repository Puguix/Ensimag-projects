using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common.Activators;
using NeuralNetwork.Common.Layers;
using NeuralNetwork.Common.Serialization;
using System;
using System.ComponentModel;
using NeuralNetwork.Common.GradientAdjustmentParameters;
using NeuralNetwork.GradientAlgorithms;
using NeuralNetwork.Gradients;
using System.Linq;

namespace NeuralNetwork.Layers
{
    internal class InputStandardizingLayer : ILayerWithWeights
    {
        public ILayerWithWeights UnderlyingLayer { get; set; }
        public double[] Mean { get; set; }
        public double[] StdDev { get; set; }


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

        public InputStandardizingLayer(ILayerWithWeights layer, int batchSize, double[] mean, double[] stdDev)
        {
            UnderlyingLayer = layer;
            Mean = mean;
            StdDev = stdDev;
            LayerSize = layer.LayerSize;
            InputSize = layer.InputSize;
            this.batchSize = batchSize;
            Activation = layer.Activation;
            WeightedError = layer.WeightedError;
            Weights = layer.Weights;
        }

        public void Propagate(Matrix<double> input)
        {
            Matrix<double> meanMatrix = Matrix<double>.Build.DenseOfColumnArrays(Mean).Multiply(Matrix<double>.Build.Dense(1, input.ColumnCount, 1));
            Matrix<double> stdDevMatrix = Matrix<double>.Build.DenseOfColumnArrays(StdDev).Multiply(Matrix<double>.Build.Dense(1, input.ColumnCount, 1));

            (input.Subtract(meanMatrix)).PointwiseDivide(stdDevMatrix);

            UnderlyingLayer.Propagate(input);
            Activation = UnderlyingLayer.Activation;
        }

        public void BackPropagate(Matrix<double> upstreamWeightedErrors)
        {
            UnderlyingLayer.BackPropagate(upstreamWeightedErrors);
            this.WeightedError = UnderlyingLayer.WeightedError;

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
            InputStandardizingLayer otherStandardizing = (InputStandardizingLayer)other;
            if (otherStandardizing.UnderlyingLayer != this.UnderlyingLayer) return false;
            return true;
        }
    }
}