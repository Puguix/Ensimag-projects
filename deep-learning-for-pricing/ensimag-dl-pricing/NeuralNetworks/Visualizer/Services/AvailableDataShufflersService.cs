using System.Collections.Generic;
using Trainer.DataShufflers;

namespace Visualizer.Services
{
    internal class AvailableDataShufflersService
    {
        public List<DataShufflerInfo> GetDataShufflers()
        {
            return new List<DataShufflerInfo>
            {
                new DataShufflerInfo("No shuffling", new NoShuffle()),
                new DataShufflerInfo("Uniform shuffling", new UniformShuffle())
            };
        }
    }
}