using System;

namespace NeuralNetwork.Common.Activators
{
    public class LeakyReLU : IActivator
    {
        public Func<double, double> Apply => (x) => (0 < x) ? x : 0.01 * x;

        public Func<double, double> ApplyDerivative => (x) => (0 < x) ? 1 : 0.01;

        public ActivatorType Type => ActivatorType.LeakyReLU;
    }
}