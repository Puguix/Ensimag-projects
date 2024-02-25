using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common.Activators;
using NeuralNetwork.Common.GradientAdjustmentParameters;
using NeuralNetwork.Layers;
using System;
using System.Collections.Generic;
using System.Text;

namespace NeuralNetwork.GradientAlgorithms
{
    public class AdamAlgorithm : IGradientAlgo
    {
        public AdamParameters AdamParameters { get; }
        private Matrix<double> WeightsFirstMomentVariable { get; set; }
        private Matrix<double> WeightsSecondMomentVariable { get; set; }
        private Matrix<double> BiasFirstMomentVariable { get; set; }
        private Matrix<double> BiasSecondMomentVariable { get; set; }


        public GradientAdjustmentType type => GradientAdjustmentType.Adam;

        public AdamAlgorithm(AdamParameters AdamParameters, int weightsRows, int weightsColumn, int biasRows, int biasColumn)
        {
            this.AdamParameters = AdamParameters;
            this.WeightsFirstMomentVariable = Matrix<double>.Build.Dense(weightsRows, weightsColumn, 0);
            this.WeightsSecondMomentVariable = Matrix<double>.Build.Dense(weightsRows, weightsColumn, 0);
            this.BiasFirstMomentVariable = Matrix<double>.Build.Dense(biasRows, biasColumn, 0);
            this.BiasSecondMomentVariable = Matrix<double>.Build.Dense(biasRows, biasColumn, 0);
        }


        public Matrix<double> UpdateWeightGrad(Matrix<double> gradients)
        {
            WeightsFirstMomentVariable = WeightsFirstMomentVariable.Multiply(AdamParameters.FirstMomentDecay).Add(gradients.Multiply(1-AdamParameters.FirstMomentDecay));
            WeightsSecondMomentVariable = WeightsSecondMomentVariable.Multiply(AdamParameters.SecondMomentDecay).Add(gradients.PointwiseMultiply(gradients).Multiply(1-AdamParameters.SecondMomentDecay));
            Matrix<double> adjustedFirstMoment = WeightsFirstMomentVariable.Divide(1 - AdamParameters.FirstMomentDecay);
            Matrix<double> adjustedSecondMoment = WeightsSecondMomentVariable.Divide(1 -AdamParameters.SecondMomentDecay);
            Matrix<double> gradientAdjustment = adjustedFirstMoment.PointwiseDivide(adjustedSecondMoment.PointwiseSqrt().Add(AdamParameters.DenominatorFactor)).Multiply(-AdamParameters.StepSize);
            return gradientAdjustment;
        }

        public Matrix<double> UpdateBiasGrad(Matrix<double> gradients)
        {
            BiasFirstMomentVariable = BiasFirstMomentVariable.Multiply(AdamParameters.FirstMomentDecay).Add(gradients.Multiply(1 - AdamParameters.FirstMomentDecay));
            BiasSecondMomentVariable = BiasSecondMomentVariable.Multiply(AdamParameters.SecondMomentDecay).Add(gradients.PointwiseMultiply(gradients).Multiply(1 - AdamParameters.SecondMomentDecay));
            Matrix<double> adjustedFirstMoment = BiasFirstMomentVariable.Divide(1 - AdamParameters.FirstMomentDecay);
            Matrix<double> adjustedSecondMoment = BiasSecondMomentVariable.Divide(1 - AdamParameters.SecondMomentDecay);
            Matrix<double> gradientAdjustment = adjustedFirstMoment.PointwiseDivide(adjustedSecondMoment.PointwiseSqrt().Add(AdamParameters.DenominatorFactor)).Multiply(-AdamParameters.StepSize);
            return gradientAdjustment;
        }


    }
}
