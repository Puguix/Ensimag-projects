using NeuralNetwork.Common;

namespace Visualizer.NetworkInfo
{
    internal class NetworkSummary
    {
        public NetworkSummary(INetwork network)
        {
            BatchSize = network.BatchSize;
            LayerNb = network.Layers.Length;
            Layers = new LayerSummary[LayerNb];
            for (int i = 0; i < LayerNb; i++)
            {
                Layers[i] = new LayerSummary(network.Layers[i], i);
            }
        }

        public int BatchSize { get; }
        public int LayerNb { get; }
        public LayerSummary[] Layers { get; }
    }
}