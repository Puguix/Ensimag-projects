using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common.Activators;
using NeuralNetwork.Common.GradientAdjustmentParameters;
using NeuralNetwork.Layers;
using System;
using System.Collections.Generic;
using System.Text;

namespace NeuralNetwork.GradientAlgorithms
{
    public class MomentumAlgorithm : IGradientAlgo
    {
        public MomentumParameters MomentumParameters { get; }
        private Matrix<double> LastWeightV { get; set; }
        private Matrix<double> LastBiasV { get; set; }

        public GradientAdjustmentType type => GradientAdjustmentType.Momentum;

        public MomentumAlgorithm(MomentumParameters momentumParameters, int weightsRows, int weightsColumn, int biasRows, int biasColumn)
        {
            this.MomentumParameters = momentumParameters;
            this.LastWeightV = Matrix<double>.Build.Dense(weightsRows,weightsColumn,0);
            this.LastBiasV = Matrix<double>.Build.Dense(biasRows,biasColumn, 0);
        }


        public Matrix<double> UpdateWeightGrad(Matrix<double> gradients)
        {
            LastWeightV = ComputeV(gradients, LastWeightV);
            return LastWeightV;
        }

        public Matrix<double> UpdateBiasGrad(Matrix<double> gradients)
        {
            LastBiasV = ComputeV(gradients, LastBiasV);
            return LastBiasV;
        }

        private Matrix<double> ComputeV(Matrix<double> gradients, Matrix<double> V)
        {
            return V.Multiply(this.MomentumParameters.Momentum).Subtract(gradients.Multiply(this.MomentumParameters.LearningRate));
        }


    }
}
