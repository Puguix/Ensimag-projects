using NeuralNetwork.Common.Layers;

namespace NeuralNetwork.Common.Serialization
{
    /// <summary>
    /// Definition of the serialization of a layer with an L2 penalty.
    /// </summary>
    /// <seealso cref="NeuralNetwork.Common.Serialization.ISerializedLayer" />
    public class SerializedL2PenaltyLayer : ISerializedLayer
    {
        public SerializedL2PenaltyLayer(ISerializedLayer underlyingSerializedLayer, double penaltyCoefficient)
        {
            UnderlyingSerializedLayer = underlyingSerializedLayer;
            PenaltyCoefficient = penaltyCoefficient;
        }

        public SerializedL2PenaltyLayer() { }

        public LayerType Type => LayerType.L2Penalty;

        public ISerializedLayer UnderlyingSerializedLayer { get; set; }
        public double PenaltyCoefficient { get; set; }
    }
}