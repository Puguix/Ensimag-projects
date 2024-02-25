using NeuralNetwork.GradientAccelerators;
using NeuralNetwork.GradientAccelerators.None;
using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Visualizer.Configuration.GradientAccelerators
{
    class NoAcceleratorConfigViewModel : BindableBase, IAcceleratorConfigViewModel
    {
        private double learningRate;

        public double LearningRate
        {
            get => learningRate;
            set => SetProperty(ref learningRate, value);
        }

        public IGradientAcceleratorParameters MakeParameters()
        {
            return new NoAcceleratorParameters(LearningRate);
        }
    }
}
