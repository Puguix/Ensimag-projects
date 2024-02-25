using MathNet.Numerics.Distributions;
using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common.Activators;
using NeuralNetwork.Common.GradientAdjustmentParameters;
using NeuralNetwork.Common.Layers;
using NeuralNetwork.Common.Serialization;
using NeuralNetwork.Layers;
using System;

namespace NeuralNetwork.Serialization
{
    internal static class LayerDeserializer
    {
        public static ILayer Deserialize(ISerializedLayer serializedLayer, int batchSize)
        {
            switch (serializedLayer.Type)
            {
                case LayerType.Standard:
                    var standardSerialized = serializedLayer as SerializedStandardLayer;
                    return DeserializeStandardLayer(standardSerialized, batchSize);
                case LayerType.L2Penalty:
                    var l2Serialized = serializedLayer as SerializedL2PenaltyLayer;
                    return DeserializeL2Layer(l2Serialized, batchSize);
                case LayerType.L1Penalty:
                    var l1Serialized = serializedLayer as SerializedL1PenaltyLayer;
                    return DeserializeL1Layer(l1Serialized, batchSize);
                case LayerType.Dropout:
                    var dropoutSerialized = serializedLayer as SerializedDropoutLayer;
                    return DeserializeDropoutLayer(dropoutSerialized, batchSize);
                case LayerType.InputStandardizing:
                    var inputStandardizingSerialized = serializedLayer as SerializedInputStandardizingLayer;
                    return DeserializeInputStandardizing(inputStandardizingSerialized, batchSize);
                default:
                    throw new InvalidOperationException("Unknown layer type to deserialize");
            }
        }
        private static ILayer DeserializeStandardLayer(SerializedStandardLayer standardSerialized, int batchSize)
        {
            var weights = Matrix<double>.Build.DenseOfRowArrays(standardSerialized.Weights);
            var bias = Matrix<double>.Build.DenseOfColumnArrays( standardSerialized.Bias );
            var activator = ActivatorFactory.Build(standardSerialized.ActivatorType);
            return new StandardLayer(weights, bias, batchSize, activator, standardSerialized.GradientAdjustmentParameters);
        }

        private static ILayer DeserializeL2Layer(SerializedL2PenaltyLayer l2Serialized, int batchSize)
        {
            ILayer underlyingLayer = Deserialize(l2Serialized.UnderlyingSerializedLayer, batchSize);
            return new L2Layer((ILayerWithWeights) underlyingLayer, batchSize,  l2Serialized.PenaltyCoefficient);
        }

        private static ILayer DeserializeL1Layer(SerializedL1PenaltyLayer l1Serialized, int batchSize)
        {
            ILayer underlyingLayer = Deserialize(l1Serialized.UnderlyingSerializedLayer, batchSize);
            return new L1Layer((ILayerWithWeights)underlyingLayer, l1Serialized.PenaltyCoefficient);
        }

        private static ILayer DeserializeDropoutLayer(SerializedDropoutLayer dropoutSerialized, int batchSize)
        {
            return new DropoutLayer(dropoutSerialized.LayerSize, dropoutSerialized.KeepProbability, batchSize);
        }

        private static ILayer DeserializeInputStandardizing(SerializedInputStandardizingLayer inputStandardizingSerialized, int batchSize)
        {
            ILayer underlyingLayer = Deserialize(inputStandardizingSerialized.UnderlyingSerializedLayer, batchSize);
            return new InputStandardizingLayer((ILayerWithWeights)underlyingLayer, batchSize, inputStandardizingSerialized.Mean, inputStandardizingSerialized.StdDev);
        }
    }
}