using System;

namespace Trainer.CostFunctions
{
    public class QuadraticError : ICostFunction
    {
        private static readonly Func<double, double, double> quad = (x, y) => 0.5 * (x - y) * (x - y);
        private static readonly Func<double, double, double> diff = (actual, expected) => actual - expected;
        public Func<double, double, double> Apply => quad;
        public Func<double, double, double> DerivApply => diff;
    }
}