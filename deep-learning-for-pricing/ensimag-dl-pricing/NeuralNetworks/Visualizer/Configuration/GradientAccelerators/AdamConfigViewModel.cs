using NeuralNetwork.GradientAccelerators;
using NeuralNetwork.GradientAccelerators.Adam;
using Prism.Mvvm;
using System;

namespace Visualizer.Configuration.GradientAccelerators
{
    class AdamConfigViewModel : BindableBase, IAcceleratorConfigViewModel
    {
        private double stepSize;
        private double firstMomentDecay;
        private double secondMomentDecay;
        private double denominatorFactor;

        public double StepSize
        {
            get => stepSize;
            set => SetProperty(ref stepSize, value);
        }

        public double FirstMomentDecay
        {
            get => firstMomentDecay;
            set => SetProperty(ref firstMomentDecay, value);
        }
        public double SecondMomentDecay
        {
            get => secondMomentDecay;
            set => SetProperty(ref secondMomentDecay, value);
        }
        public double DenominatorFactor
        {
            get => denominatorFactor;
            set => SetProperty(ref denominatorFactor, value);
        }
        public IGradientAcceleratorParameters MakeParameters()
        {
            return new AdamParameters(StepSize, FirstMomentDecay, SecondMomentDecay, DenominatorFactor);
        }

        public AdamConfigViewModel()
        {
            StepSize = 0.001;
            FirstMomentDecay = 0.9;
            SecondMomentDecay = 0.999;
            DenominatorFactor = 1E-8;
        }

    }
}
