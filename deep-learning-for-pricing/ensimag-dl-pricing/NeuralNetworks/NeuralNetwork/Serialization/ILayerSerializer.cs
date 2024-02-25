using NeuralNetwork.Common.Layers;
using NeuralNetwork.Common.Serialization;

namespace NeuralNetwork.Serialization
{
    /// <summary>
    /// Interface for classes that serialized layers.
    /// </summary>
    public interface ILayerSerializer
    {
        ISerializedLayer Serialize(ILayer layer);
    }
}