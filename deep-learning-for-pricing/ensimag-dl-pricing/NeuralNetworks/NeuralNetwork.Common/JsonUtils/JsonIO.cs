using NeuralNetwork.Common.Serialization;
using System;
using System.Collections.Generic;
using System.Text;
using System.Text.Json.Serialization;
using System.Text.Json;
using System.IO;

namespace NeuralNetwork.Common.JsonUtils
{
    public static class JsonIO
    {
        public static SerializedNetwork DeserializeNetworkFromFile(string filename)
        {
            var result = DeserializeNetworkFromString(File.ReadAllText(filename));
            return result;
        }

        public static SerializedNetwork DeserializeNetworkFromString(string jsonString)
        {
            var options = new JsonSerializerOptions()
            {
                Converters = { new JsonStringEnumConverter(), new SerializedLayerJsonConverter(), new GradientAdjustmentParametersJsonConverter() }
            };
            var result = JsonSerializer.Deserialize<SerializedNetwork>(jsonString, options);
            return result;
        }

        public static string SerializeNetworkToString(SerializedNetwork network)
        {
            var options = new JsonSerializerOptions()
            {
                Converters = { new JsonStringEnumConverter(), new SerializedLayerJsonConverter(), new GradientAdjustmentParametersJsonConverter() }
            };
            var result = JsonSerializer.Serialize<SerializedNetwork>(network, options);
            return result;
        }

        public static void SerializeNetworkToFile(SerializedNetwork network, string filename)
        {
            var jsonString = SerializeNetworkToString(network);
            File.WriteAllText(filename, jsonString);
        }
    }
}
