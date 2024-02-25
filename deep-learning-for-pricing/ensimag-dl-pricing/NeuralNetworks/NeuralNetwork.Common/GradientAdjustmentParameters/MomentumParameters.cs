namespace NeuralNetwork.Common.GradientAdjustmentParameters
{
    /// <summary>
    /// Parameters for adjusting the gradient update using the Momentum technique.
    /// </summary>
    /// <seealso cref="NeuralNetwork.Common.GradientAdjustmentParameters.IGradientAdjustmentParameters" />
    public class MomentumParameters : IGradientAdjustmentParameters
    {
        public GradientAdjustmentType Type => GradientAdjustmentType.Momentum;

        public double LearningRate { get; set; }
        public double Momentum { get; set; }

        public MomentumParameters()
        {
        }
    }
}