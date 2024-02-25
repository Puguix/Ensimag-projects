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
    public interface ILayerWithWeights : ILayer
    {
        Matrix<double> Weights { get; set; }

        Matrix<double> WeightedError { get; set; }
    }
}