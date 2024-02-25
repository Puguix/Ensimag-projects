using System;

namespace NeuralNetwork.Common.Activators
{
    public class Tanh : IActivator
    {
        private static Func<double, double> TanhApply => (x) => 2.0 / (1 + Math.Exp(-2 * x)) - 1;

        public Func<double, double> Apply => TanhApply;

        public Func<double, double> ApplyDerivative => (x) => { var tmp = TanhApply(x); return 1 - tmp * tmp; };

        public ActivatorType Type => ActivatorType.Tanh;
    }
}