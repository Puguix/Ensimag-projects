using NeuralNetwork.EvaluationFunctions;
using NeuralNetwork.Structure;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Visualizer.Services
{
    static class EvaluationFunctionFactory
    {
        public static IEvaluator MakeEvaluationFunction(Network network, EvaluationFunctionTypes type)
        {
            switch (type)
            {
                case EvaluationFunctionTypes.MatchesCount:
                    return new MatchesCounter(network.TestBatchSize);
                case EvaluationFunctionTypes.L2:
                    return new L2Error(network.OutputSize, network.TestBatchSize);
                default:
                    throw new InvalidOperationException();
            }
        }
    }
}
