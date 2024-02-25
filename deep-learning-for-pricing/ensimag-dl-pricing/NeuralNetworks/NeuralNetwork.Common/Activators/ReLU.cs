using System;

namespace NeuralNetwork.Common.Activators
{
    public class ReLU : IActivator
    {
        public Func<double, double> Apply => (x) => (0 < x) ? x : 0;

        public Func<double, double> ApplyDerivative => (x) => (0 < x) ? 1 : 0;

        public ActivatorType Type => ActivatorType.ReLU;
    }
}