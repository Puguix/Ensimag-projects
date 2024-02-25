using NeuralNetwork.Common.Layers;
using NeuralNetwork.Common.Serialization;

namespace NeuralNetwork.Serialization
{
    public static class NetworkDeserializer
    {
        public static Network Deserialize(SerializedNetwork serializedNetwork)
        {
            var serializedLayers = serializedNetwork.SerializedLayers;
            var layers = new ILayer[serializedLayers.Length];
            var batchSize = serializedNetwork.BatchSize;
            for (int i = 0; i < serializedLayers.Length; i++)
            {
                layers[i] = LayerDeserializer.Deserialize(serializedLayers[i], batchSize);
            }
            return new Network(layers, serializedNetwork.BatchSize);
        }
    }
}