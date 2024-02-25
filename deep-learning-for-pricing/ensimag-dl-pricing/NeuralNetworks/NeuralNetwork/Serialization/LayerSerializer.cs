    using NeuralNetwork.Common.Layers;
using NeuralNetwork.Common.Serialization;
using NeuralNetwork.Layers;
using System;

namespace NeuralNetwork.Serialization
{
    internal class LayerSerializer : ILayerSerializer
    {
        public ISerializedLayer Serialize(ILayer layer)
        {
            switch (layer)
            {
                case StandardLayer standardLayer:
                    return SerializeStandardLayer(standardLayer);
                case L2Layer l2Layer:
                    return SerializeL2Layer(l2Layer);
                case L1Layer l1Layer:
                    return SerializeL1Layer(l1Layer);
                case DropoutLayer dropoutLayer:
                    return SerializeDropoutLayer(dropoutLayer);
                case InputStandardizingLayer inputStandardizingLayer:
                    return SerializeInputStandardizing(inputStandardizingLayer);
                default:
                    throw new InvalidOperationException("Unknown layer type: " + layer.GetType());
            }
        }

        private ISerializedLayer SerializeStandardLayer(StandardLayer standardLayer)
        {
            double[] bias = standardLayer.Bias.ToRowMajorArray();
            double[][] weights = standardLayer.Weights.ToRowArrays();
            ISerializedLayer serializedStandardLayer = new SerializedStandardLayer(bias, weights, standardLayer.Activator.Type, standardLayer.GradParameters);
            return serializedStandardLayer;
        }

        private ISerializedLayer SerializeL2Layer(L2Layer l2Layer)
        {
            ISerializedLayer serializedUnderlyingLayer = Serialize(l2Layer.UnderlyingLayer);
            ISerializedLayer serializedL2Layer = new SerializedL2PenaltyLayer(serializedUnderlyingLayer, l2Layer.K);
            return serializedL2Layer;
        }

        private ISerializedLayer SerializeL1Layer(L1Layer l1Layer)
        {
            ISerializedLayer serializedUnderlyingLayer = Serialize(l1Layer.UnderlyingLayer);
            ISerializedLayer serializedL1Layer = new SerializedL1PenaltyLayer(serializedUnderlyingLayer, l1Layer.K);
            return serializedL1Layer;
        }

        private ISerializedLayer SerializeDropoutLayer(DropoutLayer dropoutLayer)
        {
            ISerializedLayer serializedDropoutLayer = new SerializedDropoutLayer(dropoutLayer.LayerSize , dropoutLayer.KeepProbability);
            return serializedDropoutLayer;
        }

        private ISerializedLayer SerializeInputStandardizing(InputStandardizingLayer inputStandardizingLayer)
        {
            ISerializedLayer serializedUnderlyingLayer = Serialize(inputStandardizingLayer.UnderlyingLayer);
            ISerializedLayer serializedInputStandardizingLayer = new SerializedInputStandardizingLayer(serializedUnderlyingLayer, inputStandardizingLayer.Mean, inputStandardizingLayer.StdDev);
            return serializedInputStandardizingLayer;
        }
    }
}