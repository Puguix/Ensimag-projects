using System;

namespace NeuralNetwork.Common.Activators
{
    public interface IActivator
    {
        /// <summary>
        /// Applies the activator function. To be applied to the net input of a layer.
        /// </summary>
        /// <value>
        /// The function to apply.
        /// </value>
        Func<double, double> Apply { get; }

        /// <summary>
        /// Derivative of the activator function. To be applied to activated neurons.
        /// </summary>
        /// <value>
        /// The derivative, applied to the activated neurons.
        /// </value>
        Func<double, double> ApplyDerivative { get; }

        ActivatorType Type { get; }
    }
}