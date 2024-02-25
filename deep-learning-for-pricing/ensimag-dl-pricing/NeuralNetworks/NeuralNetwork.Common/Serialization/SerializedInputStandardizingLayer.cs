using NeuralNetwork.Common.Layers;

namespace NeuralNetwork.Common.Serialization
{
    /// <summary>
    /// Definition of the serialization of an input standardizing layer.
    /// </summary>
    /// <seealso cref="NeuralNetwork.Common.Serialization.ISerializedLayer" />
    public class SerializedInputStandardizingLayer : ISerializedLayer
    {
        public SerializedInputStandardizingLayer(ISerializedLayer underlyingSerializedLayer, double[] mean, double[] stdDev)
        {
            UnderlyingSerializedLayer = underlyingSerializedLayer;
            Mean = mean;
            StdDev = stdDev;
        }

        public SerializedInputStandardizingLayer()
        {
        }

        public ISerializedLayer UnderlyingSerializedLayer { get; set; }
        public double[] Mean { get; set; }
        public double[] StdDev { get; set; }
        public LayerType Type => LayerType.InputStandardizing;
    }
}