# Deep Learning for Pricing

## Lecture notes

1. Introduction, forward propagation [slides](document/handout1.pdf)
2. Backpropagation [slides](document/handout2.pdf)
3. Mini-batch, improving gradient descent [slides](document/handout3.pdf)
4. Some network tuning, regularization [slides](document/handout4.pdf)
5. Feature preprocessing, batch normalization [slides](document/handout5.pdf)
6. On the environmental impact of deep learning [slides](document/handout6.pdf)

## Project

1. Project description [slides](document/hands-on-project.pdf)
2. Available source code and samples [folder](ensimag-dl-pricing)

### Serialized network to produce

The serialized network provided by group `i`should be of the form `network_i.json`.

### Source code to produce

The source code should be submitted as a `.zip` archive, group `i` should produce an archive named `Group_i.zip`. This archive is a zipped folder, the folder name should be `Group_i`, and should contain all the **cleaned-up** `C#` projects:

```
Group_i/
    |- NeuralNetwork.Common
    |- NeuralNetwork
    |- PropagationComparison
    |- ...
```

In particular:

-   The zipped archive should not contain any `Python` file or `_MACOSX` folder (for Mac users).
-   All Nuget packages must have the same version.

### Archive verification

The [validate_build](document/validate_build.py) can be used to make sure the submitted archive compiles correctly.

Usage:

```bash
python.exe .\validate_build.py --sln=<path-to-zip.zip> --build=<absolute-path-to-build-folder> --name=<unzipped-solution-name>
```
