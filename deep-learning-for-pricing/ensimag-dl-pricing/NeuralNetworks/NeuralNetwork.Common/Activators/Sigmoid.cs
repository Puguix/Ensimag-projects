using System;

namespace NeuralNetwork.Common.Activators
{
    public class Sigmoid : IActivator
    {
        private static readonly Func<double, double> sigmoid = (x) => 1.0 / (1 + Math.Exp(-x));

        public Func<double, double> Apply => sigmoid;

        public ActivatorType Type => ActivatorType.Sigmoid;

        public Func<double, double> ApplyDerivative => (x) => { var tmp = sigmoid(x); return tmp * (1 - tmp); };
    }
}