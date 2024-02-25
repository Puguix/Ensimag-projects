using CsvHelper;
using DataProviders;
using NeuralNetwork.Common.JsonUtils;
using NeuralNetwork.Serialization;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Text.Json;
using System.Text.Json.Serialization;
using Trainer;
using Trainer.CostFunctions;
using Trainer.DataShufflers;
using TrainingConsole;

var serializedNetwork = JsonIO.DeserializeNetworkFromFile(args[0]);
var network = NetworkDeserializer.Deserialize(serializedNetwork);
var options = new JsonSerializerOptions()
{
    Converters = { new JsonStringEnumConverter() }
};
var trainParams = JsonSerializer.Deserialize<TrainingParams>(File.ReadAllText(args[1]), options);
var dataProvider = DataProviderConverter.Convert(trainParams.ProviderType);
var data = dataProvider.GetData();
var trainingData = data.TrainingData;
var validationData = data.ValidationData;
IDataShuffler dataShuffler = trainParams.Shuffle ? new UniformShuffle() : new NoShuffle();
var runner = new NetworkTrainer(network, new QuadraticError(), dataShuffler);
var errors = new List<ErrorSummary>();
for (int i = 0; i < trainParams.EpochNb; i++)
{
    runner.Train(trainingData);
    if (i % trainParams.ValidationStep == 0)
    {
        var currentValidationError = runner.Validate(validationData);
        var currentTrainingError = runner.Validate(trainingData);
        errors.Add(new ErrorSummary(i, currentTrainingError, currentValidationError));
        System.Console.WriteLine($"Epoch {i+1}/{trainParams.EpochNb}. Training error {currentTrainingError} -- Validation error {currentValidationError}");
    }
}
var serializedContent = JsonSerializer.Serialize(NetworkSerializer.Serialize(network), options);
File.WriteAllText(args[2], serializedContent);
using (var writer = new StreamWriter(args[3]))
using (var csv = new CsvWriter(writer, CultureInfo.InvariantCulture))
{
    csv.WriteRecords(errors);
}