namespace NeuralNetwork.Common.Layers
{
    /// <summary>
    /// Types of layers that can be implemented.
    /// </summary>
    public enum LayerType
    {
        Standard,
        InputStandardizing,
        Dropout,
        L2Penalty,
        WeightDecay,
        L1Penalty,
        ElasticPenalty
    }
}