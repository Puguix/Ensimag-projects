using NeuralNetwork.EvaluationFunctions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Visualizer.Services
{
    class EvaluationFunctionInfo
    {
        public EvaluationFunctionInfo(string name, EvaluationFunctionTypes type)
        {
            Name = name;
            Type = type;
        }

        public string Name { get; }
        public EvaluationFunctionTypes Type { get; }
    }
}
