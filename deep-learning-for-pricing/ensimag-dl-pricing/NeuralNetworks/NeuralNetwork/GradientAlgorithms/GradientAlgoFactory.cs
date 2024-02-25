using MathNet.Numerics.LinearAlgebra;
using MathNet.Numerics.LinearAlgebra.Complex;
using NeuralNetwork.Common.Activators;
using NeuralNetwork.Common.GradientAdjustmentParameters;
using NeuralNetwork.GradientAlgorithms;
using System;
using System.Collections.Generic;
using System.Text;

namespace NeuralNetwork.Gradients
{
    public static class GradientAlgoFactory
    {
        public static IGradientAlgo Build(IGradientAdjustmentParameters gradParameters, Matrix<double> weights, Matrix<double> bias)
        {
            switch (gradParameters)
            {
                case AdamParameters adamParameters:
                    return new AdamAlgorithm(adamParameters, weights.RowCount, weights.ColumnCount, bias.RowCount, bias.ColumnCount) ;

                case MomentumParameters momentumParameters:
                    return new MomentumAlgorithm(momentumParameters, weights.RowCount, weights.ColumnCount, bias.RowCount, bias.ColumnCount);

                case NesterovParameters nesterovParameters:
                    return new NesterovAlgorithm(nesterovParameters,weights, bias);

                case FixedLearningRateParameters fixedLearningRateParameters:
                    return new FixedLearningRateAlgo(fixedLearningRateParameters);

                default:
                    throw new InvalidOperationException("Unknown gradient parameters type: " + gradParameters.Type.ToString());
            }
        }
    }
}
