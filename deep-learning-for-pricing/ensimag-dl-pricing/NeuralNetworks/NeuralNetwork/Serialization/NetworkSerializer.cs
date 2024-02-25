using NeuralNetwork.Common;
using NeuralNetwork.Common.Serialization;

namespace NeuralNetwork.Serialization
{
    public static class NetworkSerializer
    {
        private static ILayerSerializer layerSerializer = new LayerSerializer();

        public static SerializedNetwork Serialize(INetwork network)
        {
            var batchSize = network.BatchSize;
            var layers = network.Layers;
            var serializedLayers = new ISerializedLayer[layers.Length];
            for (int i = 0; i < layers.Length; i++)
            {
                serializedLayers[i] = layerSerializer.Serialize(layers[i]);
            }
            return new SerializedNetwork() { BatchSize = batchSize, SerializedLayers = serializedLayers };
        }
    }
}