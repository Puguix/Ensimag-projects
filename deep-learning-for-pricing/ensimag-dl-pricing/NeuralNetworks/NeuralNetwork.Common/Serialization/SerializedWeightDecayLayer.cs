using NeuralNetwork.Common.Layers;

namespace NeuralNetwork.Common.Serialization
{
    /// <summary>
    /// Definition of the serialization of a layer with weight decay regularization.
    /// </summary>
    /// <seealso cref="NeuralNetwork.Common.Serialization.ISerializedLayer" />
    public class SerializedWeightDecayLayer : ISerializedLayer
    {
        public SerializedWeightDecayLayer(ISerializedLayer underlyingSerializedLayer, double decayRate)
        {
            UnderlyingSerializedLayer = underlyingSerializedLayer;
            DecayRate = decayRate;
        }

        public SerializedWeightDecayLayer() { }
        public LayerType Type => LayerType.WeightDecay;

        public ISerializedLayer UnderlyingSerializedLayer { get; set; }
        public double DecayRate { get; set; }
    }
}