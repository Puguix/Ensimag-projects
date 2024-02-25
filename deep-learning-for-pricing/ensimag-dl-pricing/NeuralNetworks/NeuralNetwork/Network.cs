using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common;
using NeuralNetwork.Common.Layers;
using System;
using System.Xml.Linq;

namespace NeuralNetwork
{
    public sealed class Network : INetwork
    {

        public ILayer[] Layers { get; }
        public int LayerNb { get; }
        internal ILayer OutputLayer => Layers[LayerNb - 1];
        public Matrix<double> Output => OutputLayer.Activation;

        private Mode mode;
        public Mode Mode {
            get { return mode; }
            set
            {
                mode = value;
                int keepProbability = (mode == Mode.Evaluation) ? 0 : 1;
                foreach (var layer in Layers)
                {
                    if (layer is Layers.DropoutLayer )
                    {
                        ((Layers.DropoutLayer)layer).KeepProbability = keepProbability * ((Layers.DropoutLayer)layer).InitialKeepProbability;
                    }
                }
            }
        }

        private int batchSize;
        public int BatchSize {
            get { return batchSize; }
            set { 
                batchSize = value;
                for (int i = 0; i < LayerNb; i++) {
                    Layers[i].BatchSize = batchSize;
                }
            }
        }

        public Network(ILayer[] layers, int batchSize)
        {
            this.batchSize = batchSize;
            Layers = layers ?? throw new ArgumentNullException(nameof(layers));
            if (Layers.Length == 0)
            {
                throw new InvalidOperationException("The network must contain at least one layer");
            }
            LayerNb = Layers.Length;
        }

        public void Propagate(Matrix<double> input)
        {
            Layers[0].Propagate(input);
            for (int i = 1; i < LayerNb; i++)
            {
                Layers[i].Propagate(Layers[i - 1].Activation);
            }
        }

        public void Learn(Matrix<double> lossFunctionGradient)
        {
            BackpropAndUpdate(OutputLayer, lossFunctionGradient);
            for (int i = LayerNb - 2; i >= 0; i--)
            {
                BackpropAndUpdate(Layers[i], Layers[i + 1].WeightedError);
            }
        }

        private void BackpropAndUpdate(ILayer layer, Matrix<double> outputLayerError)
        {
            layer.BackPropagate(outputLayerError);
            layer.UpdateParameters();
        }
    }
}