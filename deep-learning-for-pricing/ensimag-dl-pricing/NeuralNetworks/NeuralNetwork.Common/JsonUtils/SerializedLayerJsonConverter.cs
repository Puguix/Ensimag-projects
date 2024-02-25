using NeuralNetwork.Common.Layers;
using NeuralNetwork.Common.Serialization;
using System;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace NeuralNetwork.Common.JsonUtils
{
    public class SerializedLayerJsonConverter : JsonConverter<ISerializedLayer>
    {
        public override ISerializedLayer Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            using (var jsonDoc = JsonDocument.ParseValue(ref reader))
            {
                var rootTypeName = jsonDoc.RootElement.GetProperty("Type").GetString() ?? throw new ArgumentNullException("root type name");
                var readEnum = Enum.Parse(typeof(LayerType), rootTypeName, true);
                switch (readEnum)
                {
                    case LayerType.Standard:
                        return jsonDoc.RootElement.Deserialize<SerializedStandardLayer>(options);
                    case LayerType.L2Penalty:
                        return jsonDoc.RootElement.Deserialize<SerializedL2PenaltyLayer>(options);
                    case LayerType.InputStandardizing:
                        return jsonDoc.RootElement.Deserialize<SerializedInputStandardizingLayer>(options);
                    case LayerType.Dropout:
                        return jsonDoc.RootElement.Deserialize<SerializedDropoutLayer>(options);
                    case LayerType.L1Penalty:
                        return jsonDoc.RootElement.Deserialize<SerializedL1PenaltyLayer>(options);
                    case LayerType.ElasticPenalty:
                        return jsonDoc.RootElement.Deserialize<SerializedElasticPenaltyLayer>(options);
                    case LayerType.WeightDecay:
                        return jsonDoc.RootElement.Deserialize<SerializedWeightDecayLayer>(options);
                    default:
                        throw new InvalidOperationException("Unknown type: " + readEnum);
                }
            }
        }
        public override void Write(Utf8JsonWriter writer, ISerializedLayer value, JsonSerializerOptions options)
        {
            switch (value)
            {
                case SerializedStandardLayer standard:
                    JsonSerializer.Serialize(writer, standard, options);
                    break;
                case SerializedL2PenaltyLayer l2:
                    JsonSerializer.Serialize(writer, l2, options);
                    break;
                case SerializedInputStandardizingLayer input:
                    JsonSerializer.Serialize(writer, input, options);
                    break;
                case SerializedDropoutLayer dropout:
                    JsonSerializer.Serialize(writer, dropout, options);
                    break;
                case SerializedL1PenaltyLayer l1:
                    JsonSerializer.Serialize(writer, l1, options);
                    break;
                case SerializedElasticPenaltyLayer elastic:
                    JsonSerializer.Serialize(writer, elastic, options);
                    break;
                case SerializedWeightDecayLayer weight:
                    JsonSerializer.Serialize(writer, weight, options);
                    break;
            }
        }

    }
}
