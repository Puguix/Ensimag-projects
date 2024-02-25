using System;

namespace NeuralNetwork.Common.Activators
{
    public class Identity : IActivator
    {
        public Func<double, double> Apply => (x) => x;

        public Func<double, double> ApplyDerivative => (x) => 1;

        public ActivatorType Type => ActivatorType.Identity;
    }
}