using NeuralNetwork.Common.Layers;

namespace NeuralNetwork.Common.Serialization
{
    /// <summary>
    /// Interface for defining serialized layers, that can be written to, e.g., Json files.
    /// </summary>
    public interface ISerializedLayer
    {
        LayerType Type { get; }
    }
}