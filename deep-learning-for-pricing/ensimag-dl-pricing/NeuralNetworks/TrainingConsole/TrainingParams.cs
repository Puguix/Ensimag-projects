using DataProviders;

namespace TrainingConsole
{
    internal class TrainingParams
    {
        public int EpochNb { get; set; }
        
        public DataProviderType ProviderType { get; set; }
        public int ValidationStep { get; set; }
        public bool Shuffle { get; set; }
    }
}
