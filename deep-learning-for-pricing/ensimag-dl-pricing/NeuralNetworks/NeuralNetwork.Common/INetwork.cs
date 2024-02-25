using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common.Layers;

namespace NeuralNetwork.Common
{
    public interface INetwork : IComponentWithMode
    {
        /// <summary>
        /// Gets or sets the size of the batch fed to the network.
        /// </summary>
        /// <value>
        /// The size of the batch.
        /// </value>
        int BatchSize { get; set; }

        /// <summary>
        /// Gets the activation of the output layer.
        /// </summary>
        /// <value>
        /// The activation of the output layer.
        /// </value>
        Matrix<double> Output { get; }

        /// <summary>
        /// Gets the set of layers in the network.
        /// </summary>
        /// <value>
        /// The layers.
        /// </value>
        ILayer[] Layers { get; }

        /// <summary>
        /// Main learning method. Should invoke backpropagation and weight updates on each layer.
        /// </summary>
        /// <param name="lossFunctionGradient">The gradient of the loss function on the output layer.</param>
        void Learn(Matrix<double> lossFunctionGradient);

        /// <summary>
        /// Main propagation method.
        /// </summary>
        /// <param name="input">The input.</param>
        void Propagate(Matrix<double> input);
    }
}