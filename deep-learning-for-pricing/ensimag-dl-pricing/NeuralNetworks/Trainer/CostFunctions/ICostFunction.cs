using System;

namespace Trainer.CostFunctions
{
    public interface ICostFunction
    {
        Func<double, double, double> DerivApply { get; }
        Func<double, double, double> Apply { get; }
    }
}