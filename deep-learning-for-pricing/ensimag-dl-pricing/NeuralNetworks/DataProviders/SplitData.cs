using NeuralNetwork.Common;

namespace DataProviders
{
    public class SplitData
    {
        public MathData TrainingData { get; }
        public MathData ValidationData { get; }
        public MathData TestData { get; }

        public SplitData(MathData trainingData, MathData validationData, MathData testData)
        {
            TrainingData = trainingData;
            ValidationData = validationData;
            TestData = testData;
        }
    }
}