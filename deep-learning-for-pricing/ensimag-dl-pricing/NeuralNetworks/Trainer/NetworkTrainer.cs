using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common;
using System;
using Trainer.CostFunctions;
using Trainer.DataShufflers;
using Trainer.Operators;

namespace Trainer
{
    public class NetworkTrainer
    {
        public NetworkTrainer(INetwork network, ICostFunction costFunction, IDataShuffler dataShuffler)
        {
            Network = network ?? throw new ArgumentNullException(nameof(network));
            CostFunction = costFunction ?? throw new ArgumentNullException(nameof(costFunction));
            DataShuffler = dataShuffler ?? throw new ArgumentNullException(nameof(dataShuffler));
            CostResult = Matrix<double>.Build.Dense(Network.Output.RowCount, Network.Output.ColumnCount);
            InitialBatchSize = Network.BatchSize;
            Network.Mode = Mode.Training;
        }

        public INetwork Network { get; }
        public ICostFunction CostFunction { get; }
        public IDataShuffler DataShuffler { get; }
        public Matrix<double> CostResult { get; private set; }
        public int InitialBatchSize { get; }



        public void Train(MathData data)
        {
            Network.Mode = Mode.Training;
            var command = new LearnCommand(Network, CostFunction);
            Run(data, command);
        }

        public double Validate(MathData data)
        {
            Network.Mode = Mode.Evaluation;
            var nbInputs = data.Inputs.ColumnCount;
            var command = new ErrorCommand(CostFunction);
            Run(data, command);
            return command.RunningError / nbInputs;
        }

        private void Run(MathData data, ICommand command)
        {
            var batchSize = InitialBatchSize;
            var shuffledData = DataShuffler.MakeShuffledData(data);
            var inputs = shuffledData.Inputs;
            var outputs = shuffledData.Outputs;
            var totalInputs = inputs.ColumnCount;
            var batchNb = totalInputs / batchSize;
            var remainingBatchSize = totalInputs % batchSize;
            var entrySize = inputs.RowCount;
            var outputSize = outputs.RowCount;
            for (int i = 0; i < batchNb; i++)
            {
                var batchMatrix = inputs.SubMatrix(0, entrySize, i * batchSize, batchSize);
                Network.Propagate(batchMatrix);
                var expectedOutputMatrix = outputs.SubMatrix(0, outputSize, i * batchSize, batchSize);
                var actualOutputMatrix = Network.Output;
                command.Execute(expectedOutputMatrix, actualOutputMatrix, CostResult);
            }
            if (remainingBatchSize != 0)
            {
                SetBatchSize(remainingBatchSize);
                var remainingBatchMatrix = inputs.SubMatrix(0, entrySize, batchNb * batchSize, remainingBatchSize);
                Network.Propagate(remainingBatchMatrix);
                var remainingExpectedOutputMatrix = outputs.SubMatrix(0, outputSize, batchNb * batchSize, remainingBatchSize);
                var remainingActualOutputMatrix = Network.Output;
                command.Execute(remainingExpectedOutputMatrix, remainingActualOutputMatrix, CostResult);
                SetBatchSize(InitialBatchSize);
            }
        }


        private void SetBatchSize(int batchSize)
        {
            Network.BatchSize = batchSize;
            CostResult = Matrix<double>.Build.Dense(Network.Output.RowCount, Network.Output.ColumnCount);
        }
    }
}