using NeuralNetwork.Common.GradientAdjustmentParameters;
using NeuralNetwork.Common.Layers;
using NeuralNetwork.Common.Serialization;
using System;
using System.Text.Json;
using System.Text.Json.Serialization;

namespace NeuralNetwork.Common.JsonUtils
{
    /// <summary>
    /// Converter for generating objects of type <see cref="IGradientAdjustmentParameters"/> from a Json object.
    /// </summary>
    public class GradientAdjustmentParametersJsonConverter : JsonConverter<IGradientAdjustmentParameters>
    {


        public override IGradientAdjustmentParameters Read(ref Utf8JsonReader reader, Type typeToConvert, JsonSerializerOptions options)
        {
            using (var jsonDoc = JsonDocument.ParseValue(ref reader))
            {
                var rootTypeName = jsonDoc.RootElement.GetProperty("Type").GetString() ?? throw new ArgumentNullException("root type name");
                var readEnum = Enum.Parse(typeof(GradientAdjustmentType), rootTypeName, true);
                switch (readEnum)
                {
                    case GradientAdjustmentType.FixedLearningRate:
                        return jsonDoc.RootElement.Deserialize<FixedLearningRateParameters>(options);
                    case GradientAdjustmentType.Adam:
                        return jsonDoc.RootElement.Deserialize<AdamParameters>(options);
                    case GradientAdjustmentType.Momentum:
                        return jsonDoc.RootElement.Deserialize<MomentumParameters>(options);
                    case GradientAdjustmentType.Nesterov:
                        return jsonDoc.RootElement.Deserialize<NesterovParameters>(options);
                    default:
                        throw new InvalidOperationException("Unknown type: " + readEnum);
                }
            }
        }

        public override void Write(Utf8JsonWriter writer, IGradientAdjustmentParameters value, JsonSerializerOptions options)
        {
            switch (value)
            {
                case FixedLearningRateParameters fix:
                    JsonSerializer.Serialize(writer, fix, options);
                    break;
                case AdamParameters adam:
                    JsonSerializer.Serialize(writer, adam, options);
                    break;
                case MomentumParameters momentum:
                    JsonSerializer.Serialize(writer, momentum, options);
                    break;
                case NesterovParameters nesterov:
                    JsonSerializer.Serialize(writer, nesterov, options);
                    break;
                default:
                    throw new InvalidOperationException($"Unknow type: {value.Type}");
            }
        }
    }
}