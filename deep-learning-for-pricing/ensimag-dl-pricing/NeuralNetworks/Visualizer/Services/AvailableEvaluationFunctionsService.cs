using NeuralNetwork.EvaluationFunctions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Visualizer.Services
{
    class AvailableEvaluationFunctionsService
    {
        public List<EvaluationFunctionInfo> GetEvaluationFunctions()
        {
            return new List<EvaluationFunctionInfo>
            {
                new EvaluationFunctionInfo("L2 error", EvaluationFunctionTypes.L2),
                new EvaluationFunctionInfo("Match counter", EvaluationFunctionTypes.MatchesCount)
            };
        }
    }
}
