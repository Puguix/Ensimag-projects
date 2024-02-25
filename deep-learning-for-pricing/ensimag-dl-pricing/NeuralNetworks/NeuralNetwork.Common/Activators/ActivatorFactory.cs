using System;

namespace NeuralNetwork.Common.Activators
{
    public static class ActivatorFactory
    {
        public static IActivator Build(ActivatorType activatorType)
        {
            switch (activatorType)
            {
                case ActivatorType.Sigmoid:
                    return new Sigmoid();

                case ActivatorType.Identity:
                    return new Identity();

                case ActivatorType.LeakyReLU:
                    return new LeakyReLU();

                case ActivatorType.Tanh:
                    return new Tanh();

                case ActivatorType.ReLU:
                    return new ReLU();

                default:
                    throw new InvalidOperationException("Unknown activator type: " + activatorType.ToString());
            }
        }
    }
}