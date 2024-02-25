namespace RegressionTester
{
    internal interface IEvaluationFunction
    {
        double EvaluateError(double expectedOutput, double actualOutput);
    }
}