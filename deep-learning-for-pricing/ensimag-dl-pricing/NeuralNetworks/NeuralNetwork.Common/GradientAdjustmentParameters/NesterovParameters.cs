using System;
using System.Collections.Generic;
using System.Text;

namespace NeuralNetwork.Common.GradientAdjustmentParameters
{
    /// <summary>
    /// Parameters for adjusting the gradient update using the Nesterov technique.
    /// </summary>
    /// <seealso cref="NeuralNetwork.Common.GradientAdjustmentParameters.IGradientAdjustmentParameters" />
    public class NesterovParameters : IGradientAdjustmentParameters
    {
        public GradientAdjustmentType Type => GradientAdjustmentType.Nesterov;

        public double LearningRate { get; set; }
        public double Momentum { get; set; }

        public NesterovParameters()
        {
        }
    }
}
