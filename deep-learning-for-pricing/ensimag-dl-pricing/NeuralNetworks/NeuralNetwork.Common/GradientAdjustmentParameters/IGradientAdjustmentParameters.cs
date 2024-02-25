

namespace NeuralNetwork.Common.GradientAdjustmentParameters
{
    /// <summary>
    /// Interface for gradient adjustment parameters.
    /// </summary>
    public interface IGradientAdjustmentParameters
    {
        GradientAdjustmentType Type { get; }
    }
}