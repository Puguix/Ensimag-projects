using Trainer.DataShufflers;

namespace Visualizer.Services
{
    internal class DataShufflerInfo
    {
        public DataShufflerInfo(string name, IDataShuffler shuffler)
        {
            Name = name;
            Shuffler = shuffler;
        }

        public string Name { get; }
        public IDataShuffler Shuffler { get; }
    }
}