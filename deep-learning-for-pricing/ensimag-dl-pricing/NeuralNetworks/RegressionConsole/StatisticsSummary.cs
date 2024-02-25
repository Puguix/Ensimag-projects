using MathNet.Numerics.Statistics;

namespace RegressionTester
{
    internal class StatisticsSummary
    {
        public double Mean { get; }
        public double StdDev { get; }
        public double Min { get; }
        public double Max { get; }
        public double Median { get; }
        public double LowerQuantile { get; }
        public double UpperQuantile { get; }

        public StatisticsSummary(double[] data)
        {
            var summary = Statistics.FiveNumberSummary(data);
            var meanStdDev = Statistics.MeanStandardDeviation(data);
            Mean = meanStdDev.Item1;
            StdDev = meanStdDev.Item2;
            Min = summary[0];
            LowerQuantile = summary[1];
            Median = summary[2];
            UpperQuantile = summary[3];
            Max = summary[4];
        }
    }
}