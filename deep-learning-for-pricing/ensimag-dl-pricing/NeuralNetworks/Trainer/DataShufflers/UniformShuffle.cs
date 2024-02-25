using MathNet.Numerics;
using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common;

namespace Trainer.DataShufflers
{
    public class UniformShuffle : IDataShuffler
    {
        private int[] Shuffle(int dataSize)
        {
            return Combinatorics.GeneratePermutation(dataSize);
        }

        public MathData MakeShuffledData(MathData data)
        {
            var trainingInputs = data.Inputs;
            var trainingOutputs = data.Outputs;
            var nbTrainingInputs = data.Inputs.ColumnCount;
            int[] perm = Shuffle(nbTrainingInputs);
            int inputSize = trainingInputs.RowCount;
            int outputSize = trainingOutputs.RowCount;
            var modifiedInputs = Matrix<double>.Build.Dense(inputSize, nbTrainingInputs);
            var modifiedOutputs = Matrix<double>.Build.Dense(outputSize, nbTrainingInputs);
            Vector<double> inputCol = Vector<double>.Build.Dense(inputSize);
            Vector<double> outputCol = Vector<double>.Build.Dense(outputSize);
            for (int j = 0; j < nbTrainingInputs; j++)
            {
                trainingInputs.Column(perm[j], inputCol);
                modifiedInputs.SetColumn(j, inputCol);
                trainingOutputs.Column(perm[j], outputCol);
                modifiedOutputs.SetColumn(j, outputCol);
            }
            return new MathData(modifiedInputs, modifiedOutputs);
        }
    }
}