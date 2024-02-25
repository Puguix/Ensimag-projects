using NeuralNetwork.Common;
using System;

namespace RegressionTester
{
    internal class Evaluator
    {
        public Evaluator(INetwork network, IEvaluationFunction evaluationFunction)
        {
            Network = network ?? throw new ArgumentNullException(nameof(network));
            EvaluationFunction = evaluationFunction ?? throw new ArgumentNullException(nameof(evaluationFunction));
        }

        public INetwork Network { get; }
        public IEvaluationFunction EvaluationFunction { get; }

        public double[] Test(MathData data)
        {
            Network.BatchSize = 1;
            Network.Mode = Mode.Evaluation;
            var inputs = data.Inputs;
            var outputs = data.Outputs;
            int totalInputs = inputs.ColumnCount;
            int entrySize = inputs.RowCount;
            var errors = new double[totalInputs];
            for (int i = 0; i < totalInputs; i++)
            {
                var inputValues = inputs.SubMatrix(0, entrySize, i, 1);
                Network.Propagate(inputValues);
                var expectedOutput = outputs[0, i];
                var actualOutput = Network.Output[0, 0];
                errors[i] = EvaluationFunction.EvaluateError(expectedOutput, actualOutput);
            }
            return errors;
        }
    }
}