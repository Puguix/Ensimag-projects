using NeuralNetwork.Common.Layers;

namespace Visualizer.NetworkInfo
{
    internal class LayerSummary
    {
        public int InputSize { get; }
        public int LayerSize { get; }
        public int LayerPosition { get; }

        public LayerSummary(ILayer layer, int position)
        {
            InputSize = layer.InputSize;
            LayerSize = layer.LayerSize;
            LayerPosition = position + 1;
        }
    }
}