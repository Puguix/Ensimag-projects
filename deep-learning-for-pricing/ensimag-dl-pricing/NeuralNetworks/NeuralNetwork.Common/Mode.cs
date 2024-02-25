namespace NeuralNetwork.Common
{
    /// <summary>
    /// Mode in which a network can be. This can be used to modify the behavior of the network between the
    /// training and evaluation phases, e.g., by modifying the behavior of the Dropout layers.
    /// </summary>
    public enum Mode
    {
        Evaluation,
        Training
    }
}