import subprocess
import os
import csv
import pandas as pd
import json
import numpy as np
import math
import matplotlib.pyplot as plt

project_root = "C:/Users/isla_/OneDrive/Bureau/IAE/cours/deep-learning-for-pricing"

examples_training_console = project_root+"/ensimag-dl-pricing/Examples/TrainingConsole"



### ###
#
#   CREATE SERIALIZED NETWORK
###

## Preparing pricing data : calculate mean and stddev for input standardization

pricing_data =pd.read_csv(project_root+"/ensimag-dl-pricing/NeuralNetworks/DataProviders/PricingData/pricing-data-inputs.csv", header=None)

# TODO calculer mean et stddev sur données entrainement seulement, pas données de validation

means = pricing_data.mean(axis=0).to_list()
stddevs = pricing_data.std().to_list()

def create_network(batch_size, layers, path):
    network = {}
    network["BatchSize"] = batch_size
    network["SerializedLayers"] = layers
    json_object = json.dumps(network, indent=4)
    with open(path, "w") as outfile:
        outfile.write(json_object)
        print("network created")

def create_standard_layer(input_size, nb_neurons, activatorType, learningRate):
    bias = np.array([0.0] * nb_neurons).tolist()
    weights = np.random.normal(0, 1/math.sqrt(input_size), size=(input_size, nb_neurons)).tolist()
    layer = {
    "Bias" : bias,
    "Weights" : weights,
    "ActivatorType" : activatorType,
    "GradientAdjustmentParameters": {
        "LearningRate": learningRate,
        "Momentum": 0.1,
        "Type": "Momentum"
        },
    "Type": "Standard"
    }
    return layer

def create_dropout_layer(layer_size, keep_probability):
    layer = {
    "LayerSize" : layer_size,
    "KeepProbability" : keep_probability,
    "Type" : "Dropout"
    }
    return layer

def create_inputstd_layer(underlying_layer, means, stddevs):
    layer = {
    "Type" : "InputStandardizing",
    "UnderlyingSerializedLayer": underlying_layer,
    "Mean" : means,
    "StdDev": stddevs
    }
    return layer

def create_l2_layer(underlying_layer, penalty_coeff):
    layer = {
    "Type" : "L2Penalty",
    "UnderlyingSerializedLayer": underlying_layer,
    "PenaltyCoefficient" : penalty_coeff,
    }
    return layer

# Pricing network

layers = []
underlying_layer = create_standard_layer(7, 7, "LeakyReLu", 0.001)
layers.append(create_inputstd_layer(underlying_layer, means, stddevs))
for i in range (1,5):
    underlying_layer = create_standard_layer(7*2**(i-1), 7*2**(i), "LeakyReLu", 0.001)
    layers.append(create_l2_layer(underlying_layer, 0.001))
    layers.append(create_dropout_layer(7*2**(i), 0.2))

for i in range (4, 0, -1):
    underlying_layer = create_standard_layer(7*2**(i), 7*2**(i-1), "LeakyReLu", 0.001)
    layers.append(create_l2_layer(underlying_layer, 0.001))
    layers.append(create_dropout_layer(7*2**(i-1), 0.2))
#layers.append(create_standard_layer(112, 7, "LeakyReLu", 0.001))

layers.append(create_standard_layer(7, 1, "Identity", 0.001))
create_network(100, layers, examples_training_console+"/network1.json")

# XOR network
layers = []
layers.append(create_standard_layer(2, 3, "LeakyReLu", 0.05))
layers.append(create_standard_layer(3, 3, "LeakyReLu", 0.05))
layers.append(create_standard_layer(3, 1, "LeakyReLu", 0.1))
create_network(2, layers, examples_training_console+"/xornetwork.json")


###
#
#   BUILD AND RUN TRAINING CONSOLE
###
project_path = project_root+'/ensimag-dl-pricing/NeuralNetworks/TrainingConsole/TrainingConsole.csproj'

# Build the project
build_command = ['dotnet', 'build', project_path]
subprocess.run(build_command, check=True)

# Run exe
executable_path = project_root+"/ensimag-dl-pricing/NeuralNetworks/TrainingConsole/bin/Debug/net7.0/TrainingConsole.exe"

pricing_network_path = examples_training_console+"/network1.json"
xor_network_path = examples_training_console+"/xornetwork.json"

pricing_description_path = examples_training_console+"/pricing_description.json"
xor_description_path = examples_training_console+"/xor_description.json"

trained_network_path = examples_training_console+"/trained_network.json"
errors_path = examples_training_console+"/errors2.csv"

subprocess.run([executable_path, pricing_network_path, pricing_description_path, trained_network_path, errors_path], check=True)


###
# retrieveing and plotting errors
###
errors1 =pd.read_csv(project_root+"/ensimag-dl-pricing/Examples/TrainingConsole/errors1.csv")
errors1.TrainingError.plot()
plt.xlabel("epoch")
plt.ylabel("Training error")
errors1.ValidationError.plot()
plt.ylabel("Validation error")
plt.show()

###
# REGRESSION CONSOLE
##
project_path = project_root+'/ensimag-dl-pricing/NeuralNetworks/RegressionConsole'

# Build the project
build_command = ['dotnet', 'build', project_path]
subprocess.run(build_command, check=True)

# Run exe
executable_path = project_root+"/ensimag-dl-pricing/NeuralNetworks/RegressionConsole/bin/Debug/net7.0/RegressionConsoleFramework.exe"

trained_network_path = examples_training_console+"/trained_network.json"
summary_path = examples_training_console+"/summary1.csv"

subprocess.run([executable_path, trained_network_path, summary_path], check=True)
