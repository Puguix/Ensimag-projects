using NeuralNetwork.Common.Layers;

namespace NeuralNetwork.Common.Serialization
{
    /// <summary>
    /// Definition of the serialization of a layer with an L2 penalty.
    /// </summary>
    /// <seealso cref="NeuralNetwork.Common.Serialization.ISerializedLayer" />
    public class SerializedL1PenaltyLayer : ISerializedLayer
    {
        public SerializedL1PenaltyLayer(ISerializedLayer underlyingSerializedLayer, double penaltyCoefficient)
        {
            UnderlyingSerializedLayer = underlyingSerializedLayer;
            PenaltyCoefficient = penaltyCoefficient;
        }

        public SerializedL1PenaltyLayer() { }

        public LayerType Type => LayerType.L1Penalty;

        public ISerializedLayer UnderlyingSerializedLayer { get; set; }
        public double PenaltyCoefficient { get; set; }
    }
}
