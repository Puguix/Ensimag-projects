using System;
using System.Collections.Generic;
using System.Text;

namespace Runner.CostFunctions
{
    public class CrossEntropyError : ICostFunction
    {
        private static readonly Func<double, double, double> crossDiff = (actual, expected) => (actual - expected)/(actual * (1 - actual));

        public Func<double, double, double> DerivApply => crossDiff;

        public string Name => "Cross-entropy";

        public CostFunctionType ToEnumType() => CostFunctionType.CrossEntropy;
    }
}
