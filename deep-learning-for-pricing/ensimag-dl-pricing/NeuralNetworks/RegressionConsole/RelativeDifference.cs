namespace RegressionTester
{
    internal class RelativeDifference : IEvaluationFunction
    {
        public double EvaluateError(double expectedOutput, double actualOutput)
        {
            return (actualOutput - expectedOutput) / expectedOutput;
        }
    }
}