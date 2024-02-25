using NeuralNetwork.Common.Layers;
using System;
using System.Collections.Generic;
using System.Text;

namespace NeuralNetwork.Common.Serialization
{
    public class SerializedElasticPenaltyLayer : ISerializedLayer
    {
        public SerializedElasticPenaltyLayer(ISerializedLayer underlyingSerializedLayer, double l1penaltyCoefficient, double l2penaltyCoefficient)
        {
            UnderlyingSerializedLayer = underlyingSerializedLayer;
            L1PenaltyCoefficient = l1penaltyCoefficient;
            L2PenaltyCoefficient = l2penaltyCoefficient;
        }

        public SerializedElasticPenaltyLayer() { }

        public ISerializedLayer UnderlyingSerializedLayer { get; set; }
        public double L1PenaltyCoefficient { get; set; }
        public double L2PenaltyCoefficient { get; set; }
        public LayerType Type => LayerType.ElasticPenalty;
    }
}
