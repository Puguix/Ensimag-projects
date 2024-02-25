using DataProviders;
using NeuralNetwork.Common;
using System;

namespace Runner
{
    public static class ShufflerFactory
    {
        public static IDataShuffler Build(ShufflerType type, MathData originalData)
        {
            switch (type)
            {
                case ShufflerType.None:
                    return new NoShuffle(originalData);
                case ShufflerType.Uniform:
                    return new UniformShuffle(originalData);
                default:
                    throw new InvalidOperationException();
            }
        }
    }
}
