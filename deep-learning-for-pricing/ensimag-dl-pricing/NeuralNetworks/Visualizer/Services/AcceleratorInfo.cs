namespace Visualizer.Services
{
    class AcceleratorInfo
    {
        public AcceleratorInfo(string name, IAcceleratorConfigViewModel acceleratorConfig)
        {
            Name = name;
            GradientAcceleratorParameters = acceleratorConfig;
        }

        public string Name { get; }
        public IAcceleratorConfigViewModel GradientAcceleratorParameters { get; }
    }
}
