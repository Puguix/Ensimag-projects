using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common.GradientAdjustmentParameters;
using System;
using System.Collections.Generic;
using System.Text;

namespace NeuralNetwork.GradientAlgorithms
{
    public interface IGradientAlgo
    {
        GradientAdjustmentType type { get; }

        public Matrix<double> UpdateWeightGrad(Matrix<double> gradients);
        public Matrix<double> UpdateBiasGrad(Matrix<double> gradients);
    }
}
