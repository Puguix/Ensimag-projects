using NeuralNetwork.Common.Layers;

namespace NeuralNetwork.Common.Serialization
{
    /// <summary>
    /// Definition of the serialization of a Dropout layer.
    /// </summary>
    /// <seealso cref="NeuralNetwork.Common.Serialization.ISerializedLayer" />
    public class SerializedDropoutLayer : ISerializedLayer
    {
        public LayerType Type => LayerType.Dropout;
        public double KeepProbability { get; set; }
        public int LayerSize { get; set; }

        public SerializedDropoutLayer()
        {
        }

        public SerializedDropoutLayer(int layerSize, double keepProbability)
        {
            KeepProbability = keepProbability;
            LayerSize = layerSize;
        }
    }
}