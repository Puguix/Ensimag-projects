namespace PropagationComparison
{
    internal class OutputSummary
    {
        public OutputSummary(double[] firstOutput, double[] secondOutput)
        {
            FirstOutput = firstOutput;
            SecondOutput = secondOutput;
        }

        public double[] FirstOutput { get; }
        public double[] SecondOutput { get; }
    }
}
