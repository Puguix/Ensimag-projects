using NeuralNetwork.Common;

namespace Trainer.DataShufflers
{
    public class NoShuffle : IDataShuffler
    {
        public MathData MakeShuffledData(MathData data)
        {
            return data;
        }
    }
}