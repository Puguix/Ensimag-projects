using MathNet.Numerics.LinearAlgebra;
using System;

namespace NeuralNetwork.Common.Layers
{
    /// <summary>
    /// General interface for defining a layer.
    /// </summary>
    /// <seealso cref="System.IEquatable{NeuralNetwork.Common.Layers.ILayer}" />
    public interface ILayer : IEquatable<ILayer>
    {
        /// <summary>
        /// Gets the size of the layer.
        /// </summary>
        /// <value>
        /// The size of the layer.
        /// </value>
        int LayerSize { get; }

        /// <summary>
        /// Gets the size of the input that is fed to the layer.
        /// </summary>
        /// <value>
        /// The size of the input.
        /// </value>
        int InputSize { get; }

        /// <summary>
        /// Gets or sets the batch size.
        /// </summary>
        /// <value>
        /// The batch size.
        /// </value>
        int BatchSize { get; set; }

        /// <summary>
        /// Propagates the specified input through the layer./>
        /// </summary>
        /// <param name="input">The input.</param>
        void Propagate(Matrix<double> input);

        /// <summary>
        /// Performs the backpropagation operation given the weighted errors of the upstream layer.
        /// </summary>
        /// <param name="upstreamWeightedErrors">The upstream weighted errors.</param>
        void BackPropagate(Matrix<double> upstreamWeightedErrors);

        /// <summary>
        /// Updates the parameters of the layer, typically its weights and bias.
        /// </summary>
        void UpdateParameters();

        /// <summary>
        /// Gets the activation of the given layer.
        /// </summary>
        /// <value>
        /// The activation of the layer.
        /// </value>
        Matrix<double> Activation { get; }

        /// <summary>
        /// Gets the weighted error, which is propagated to the preceeding layer.
        /// </summary>
        /// <value>
        /// The weighted error.
        /// </value>
        Matrix<double> WeightedError { get; }
    }
}