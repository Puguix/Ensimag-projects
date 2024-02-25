using NeuralNetwork.CostFunctions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Visualizer.Services
{
    class AvailableCostFunctionsService
    {
        public List<CostFunctionInfo> GetErrorFunctions()
        {
            return new List<CostFunctionInfo>
            {
                new CostFunctionInfo("Quadratic", CostFunctionType.Quadratic),
                new CostFunctionInfo("Cross-Entropy", CostFunctionType.CrossEntropy)
            };
        }
    }
}
