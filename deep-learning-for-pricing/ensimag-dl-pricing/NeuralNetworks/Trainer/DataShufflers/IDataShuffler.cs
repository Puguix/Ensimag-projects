using NeuralNetwork.Common;

namespace Trainer.DataShufflers
{
    public interface IDataShuffler
    {
        MathData MakeShuffledData(MathData data);
    }
}