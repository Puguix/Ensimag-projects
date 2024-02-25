using NeuralNetwork.Common.Activators;
using NeuralNetwork.Common.GradientAdjustmentParameters;
using NeuralNetwork.Common.Layers;

namespace NeuralNetwork.Common.Serialization
{
    /// <summary>
    /// Definition of the serialization of a standard layer.
    /// </summary>
    /// <seealso cref="NeuralNetwork.Common.Serialization.ISerializedLayer" />
    public class SerializedStandardLayer : ISerializedLayer
    {
        public SerializedStandardLayer(double[] bias, double[][] weights, ActivatorType activatorType, IGradientAdjustmentParameters gradientAdjustmentParameters)
        {
            Bias = bias;
            Weights = weights;
            ActivatorType = activatorType;
            GradientAdjustmentParameters = gradientAdjustmentParameters;
        }

        public SerializedStandardLayer()
        {
        }

        public double[] Bias { get; set; }
        public double[][] Weights { get; set; }
        public ActivatorType ActivatorType { get; set; }
        public IGradientAdjustmentParameters GradientAdjustmentParameters { get; set; }
        public LayerType Type => LayerType.Standard;
    }
}