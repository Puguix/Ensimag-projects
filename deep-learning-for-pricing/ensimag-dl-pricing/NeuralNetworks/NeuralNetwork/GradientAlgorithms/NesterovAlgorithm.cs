using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common.Activators;
using NeuralNetwork.Common.GradientAdjustmentParameters;
using NeuralNetwork.Layers;
using System;
using System.Collections.Generic;
using System.Text;

namespace NeuralNetwork.GradientAlgorithms
{
    public class NesterovAlgorithm : IGradientAlgo
    {
        public NesterovParameters NesterovParameters { get; }
        private double MomentumSquared { get; }
        private Matrix<double> WeightsVelocity { get; set; }
        private Matrix<double> BiasVelocity { get; set; }
        private Matrix<double> WeightsFutureGrad { get; set; }
        private Matrix<double> BiasFutureGrad { get; set; }


        public GradientAdjustmentType type => GradientAdjustmentType.Adam;

        public NesterovAlgorithm(NesterovParameters NesterovParameters, Matrix<double> weights, Matrix<double> bias)
        {
            this.NesterovParameters = NesterovParameters;
            this.MomentumSquared = NesterovParameters.Momentum * NesterovParameters.Momentum;
            this.WeightsVelocity = Matrix<double>.Build.Dense(weights.RowCount, weights.ColumnCount, 0);
            this.BiasVelocity = Matrix<double>.Build.Dense(bias.RowCount, bias.ColumnCount, 0);
            this.WeightsFutureGrad = weights;
            this.BiasFutureGrad = bias;
        }

        public Matrix<double> UpdateWeightGrad(Matrix<double> gradients)
        {
            WeightsFutureGrad.Add(WeightsVelocity.Multiply(MomentumSquared)).Subtract(gradients.Multiply(NesterovParameters.LearningRate * (1+NesterovParameters.Momentum)));
            Matrix<double> gradientAdjustment = WeightsVelocity.Multiply(NesterovParameters.Momentum).Subtract(gradients.Multiply(NesterovParameters.LearningRate));
            return gradientAdjustment;
        }

        public Matrix<double> UpdateBiasGrad(Matrix<double> gradients)
        {
            BiasFutureGrad.Add(BiasVelocity.Multiply(MomentumSquared)).Subtract(gradients.Multiply(NesterovParameters.LearningRate * (1 + NesterovParameters.Momentum)));
            Matrix<double> gradientAdjustment = BiasVelocity.Multiply(NesterovParameters.Momentum).Subtract(gradients.Multiply(NesterovParameters.LearningRate));
            return gradientAdjustment;
        }


    }
}
