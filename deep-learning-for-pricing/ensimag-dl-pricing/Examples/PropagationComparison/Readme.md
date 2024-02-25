### HowTo
- Copy-paste `network.json`, `input.csv` and `gradient.csv` from the [Simple](Simple) folder into the same folder as `PropagationComparison.exe`
- Open a powershell (or a command prompt) and execute 
    ```
    .\PropagationComparison.exe .\network.json .\input.csv .\gradient.csv
    ``` 
You will obtain a `json` output containing the outputs of the network after the first and second forward propagations.

**Nb:** A fourth argument, which is a filename can be provided (e.g. `result.json`); in this case, the json output is written in the corresponding file.