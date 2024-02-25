using MathNet.Numerics.LinearAlgebra;
using NeuralNetwork.Common;
using System;
using System.Collections.Generic;
using System.Text;
using Trainer.CostFunctions;

namespace Trainer.Operators
{
    internal class LearnCommand : ICommand
    {
        public LearnCommand(INetwork network, ICostFunction costFunction)
        {
            Network = network ?? throw new ArgumentNullException(nameof(network));
            CostFunction = costFunction ?? throw new ArgumentNullException(nameof(costFunction));
        }

        public INetwork Network { get; }
        public ICostFunction CostFunction { get; }
        
        public void Execute(Matrix<double> expectedOutputMatrix, Matrix<double> actualOutputMatrix, Matrix<double> costResult)
        {
            actualOutputMatrix.Map2(CostFunction.DerivApply, expectedOutputMatrix, costResult);
            Network.Learn(costResult);
        }
    }
}
