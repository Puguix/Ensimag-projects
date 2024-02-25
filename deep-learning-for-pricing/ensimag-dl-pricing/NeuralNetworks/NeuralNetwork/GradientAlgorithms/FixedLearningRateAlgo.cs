using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common.Activators;
using NeuralNetwork.Common.GradientAdjustmentParameters;
using System;
using System.Collections.Generic;
using System.Text;

namespace NeuralNetwork.GradientAlgorithms
{
    public class FixedLearningRateAlgo : IGradientAlgo
    {
        private double LearningRate {  get; set; }

        public GradientAdjustmentType type => GradientAdjustmentType.FixedLearningRate;

        public FixedLearningRateAlgo(FixedLearningRateParameters parameters) {
            this.LearningRate = parameters.LearningRate;
        }


        public Matrix<double> UpdateWeightGrad(Matrix<double> gradients)
        {
            return gradients.Multiply(-this.LearningRate);
        }


        public Matrix<double> UpdateBiasGrad(Matrix<double> gradients)
        {
            return gradients.Multiply(-this.LearningRate);
        }

    }
}
