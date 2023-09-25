// Stratégies systématiques

// Import packages
using CsvHelper;
using PricingLibrary.Computations;
using PricingLibrary.DataClasses;
using PricingLibrary.MarketDataFeed;
using PricingLibrary.RebalancingOracleDescriptions;
using PricingLibrary.TimeHandler;
using PricingLibrary.Utilities;
using ScottPlot;
using System.Collections.Generic;
using System.Globalization;
using System.Linq.Expressions;

// Number of arguments
string[] cmdLine = Environment.GetCommandLineArgs();
int commandLineArgc = cmdLine.Length;

// Verify if enough arguments are passed, or else exit with error
if (commandLineArgc < 4)
{
    Console.WriteLine("Error command should be: BacktestConsole.exe <test-params> <mkt-data> <output-file>");
    Environment.Exit(1);
}

// Paths to input and output data
string pathToParams = "";
string pathToData= "";
string pathToOutput= "";

// get the paths to data, parameters, and output
for (int i = 0; i < commandLineArgc; i++)
{
    switch (i)
    {
        case 1:
            pathToParams = cmdLine[i].Trim();
            Console.WriteLine(pathToParams);
            break;
        case 2:
            pathToData = cmdLine[i].Trim();
            Console.WriteLine(pathToData);
            break;
        case 3:
            pathToOutput = cmdLine[i].Trim();
            Console.WriteLine(pathToOutput);
            break;
    }
}

// Get the shares data
/*var reader = new StreamReader(pathToData);
var csv = new CsvReader(reader, CultureInfo.InvariantCulture);
IEnumerable<ShareValue> sample = csv.GetRecords<ShareValue>();*/
IEnumerable<ShareValue> sample = SampleMarketData.Sample();

// Construct the option
Basket option = new()
{
    Maturity = DateTime.Parse("2023-12-12T00:00:00"),
    UnderlyingShareIds = new string[] { "share_1" },
    Strike = 10,
    Weights = new double[] { 1 }
};

// Defines parameters for the pricer
BasketTestParameters param = new() { BasketOption = option };
double[][] correlations = new double[1][];
correlations[0] = new double[] { 1 };
double[] volatilities = new double[] { 0.2 };
param.PricingParams = new BasketPricingParameters
{
    Volatilities = volatilities,
    Correlations = correlations
};
RegularOracleDescription oracleDescription = new() { Period = 1 };
param.RebalancingOracleDescription = oracleDescription;
Pricer pricer = new(param);

// Instanciate variables for optimisation
OutputData data = new();
List<OutputData> dataValues = new();
double timeToMaturity = 0;
double[] spots = new double[1] { 0 };
PricingResults prices;
double riskFreeTokens = 0;          // Number of risk free tokens owned
double pfValue = 0;                 // Porfolio value

// Var to track if its the first iteration cause logic is not exactly the same
bool firstIteration = true;

// Lists to plot
List<DateTime> dates = new();
List<double> pf = new();
List<double> opt = new();

// Iterate over each date
foreach (ShareValue v in sample)
{
    // Print data
    Console.WriteLine($"{v.Id}: {v.DateOfPrice}   {v.Value}");

    // Update spots, timeToMaturity, and compute prices
    timeToMaturity = MathDateConverter.ConvertToMathDistance(v.DateOfPrice, option.Maturity);
    spots[0] = v.Value;
    prices = pricer.Price(timeToMaturity, spots);

    // In the first iteration, the portfolio value is the same as the option's price
    if (firstIteration)
    {
        pfValue = prices.Price;
        firstIteration = false;
    }
    // Otherwise, it is the spot value + risk free value value
    else
    {
        pfValue = data.Deltas[0] * spots[0] + riskFreeTokens * RiskFreeRateProvider.GetRiskFreeRateAccruedValue(data.Date, v.DateOfPrice);
    }

    // Update the data
    data.Deltas = prices.Deltas;
    data.DeltasStdDev = prices.DeltaStdDev;
    data.Price = prices.Price;
    data.PriceStdDev = prices.PriceStdDev;
    data.Date = v.DateOfPrice;
    data.Value = pfValue;

    // Update the number of risk free tokens owned
    Console.WriteLine($"delta {data.Deltas[0]} et prix {spots[0]}");
    riskFreeTokens = pfValue - data.Deltas[0] * spots[0]; // riskFreeTokens * RiskFreeRateProvider.GetRiskFreeRateAccruedValue(data.Date, v.DateOfPrice)

    // Add new data to the list
    dataValues.Add(data);
    dates.Add(v.DateOfPrice);
    pf.Add(pfValue);
    opt.Add(prices.Price);

    // Print data
    Console.WriteLine($"Portfolio value: {data.Value}      Price: {prices.Price}     Sans risque: {riskFreeTokens}");
}

// Create the plot
var plt = new Plot(600, 400);

// Plot the data
plt.AddScatter(dates.Select(x => x.ToOADate()).ToArray(), pf.ToArray(), label: "Portfolio");
plt.AddScatter(dates.Select(x => x.ToOADate()).ToArray(), opt.ToArray(), label: "Option price");

// Customize the axis labels
plt.Title("Couverture vs Option");
plt.XLabel("Dates");
plt.YLabel("Valeurs (€)");
plt.XAxis.DateTimeFormat(true);
plt.Legend(location:Alignment.UpperRight);

// Save figure in project\bin\x64\Debug\net7.0-windows
plt.SaveFig("graph.png");

Console.ReadKey(); // So the console does not close at the end of execution
