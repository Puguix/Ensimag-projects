using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common.JsonUtils;
using NeuralNetwork.Serialization;

var networkDescriptionFile = Environment.GetCommandLineArgs()[1];
var firstArgument = double.Parse(Environment.GetCommandLineArgs()[2]);
var secondArgument = double.Parse(Environment.GetCommandLineArgs()[3]);


var initialSerializedNetwork = JsonIO.DeserializeNetworkFromFile(networkDescriptionFile);
var currentNetwork = NetworkDeserializer.Deserialize(initialSerializedNetwork);
currentNetwork.BatchSize = 1;
var input = Matrix<double>.Build.Dense(2, 1);
input[0, 0] = firstArgument;
input[1, 0] = secondArgument;
currentNetwork.Propagate(input);
var networkRawOutput = currentNetwork.Output[0, 0];
var networkEvaluation = networkRawOutput < 0.5 ? 0 : 1;
Console.WriteLine($"Raw output: {networkRawOutput}, entailed output: {networkEvaluation}");