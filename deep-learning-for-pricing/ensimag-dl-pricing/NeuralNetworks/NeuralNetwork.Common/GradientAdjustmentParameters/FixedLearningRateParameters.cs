namespace NeuralNetwork.Common.GradientAdjustmentParameters
{
    /// <summary>
    /// Parameters for adjusting the gradient update using a fixed learning rate.
    /// </summary>
    /// <seealso cref="NeuralNetwork.Common.GradientAdjustmentParameters.IGradientAdjustmentParameters" />
    public class FixedLearningRateParameters : IGradientAdjustmentParameters
    {
        public double LearningRate { get; set; }

        public GradientAdjustmentType Type => GradientAdjustmentType.FixedLearningRate;
        

        public FixedLearningRateParameters(double learningRate)
        {
            LearningRate = learningRate;
        }
    }
}