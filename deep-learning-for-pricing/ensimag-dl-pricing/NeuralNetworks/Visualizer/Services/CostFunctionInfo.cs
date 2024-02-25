using NeuralNetwork.CostFunctions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Visualizer.Services
{
    class CostFunctionInfo
    {
        public CostFunctionInfo(string name, CostFunctionType costFunction)
        {
            Name = name;
            CostFunction = costFunction;
        }

        public string Name { get; }
        public CostFunctionType CostFunction { get; }
    }
}
