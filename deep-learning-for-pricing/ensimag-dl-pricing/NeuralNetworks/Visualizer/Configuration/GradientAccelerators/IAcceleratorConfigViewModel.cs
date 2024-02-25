using NeuralNetwork.GradientAccelerators;

namespace Visualizer.Configuration.GradientAccelerators
{
    interface IAcceleratorConfigViewModel
    {
        IGradientAcceleratorParameters MakeParameters();
    }
}