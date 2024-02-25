namespace NeuralNetwork.Common
{
    /// <summary>
    /// Interface for components that have a different behavior depending on whether the network is in training or testing mode.
    /// </summary>
    public interface IComponentWithMode
    {
        /// <summary>
        /// Gets or sets the mode of the layer.
        /// </summary>
        /// <value>
        /// The mode.
        /// </value>
        Mode Mode { get; set; }
    }
}