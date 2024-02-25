using MathNet.Numerics.LinearAlgebra;
using System;
using System.Collections.Generic;
using System.Text;
using Trainer.CostFunctions;

namespace Trainer.Operators
{
    internal class ErrorCommand : ICommand
    {        
        public double RunningError { get; private set; }
        public ICostFunction CostFunction { get; }

        public ErrorCommand(ICostFunction costFunction)
        {
            RunningError = 0;
            CostFunction = costFunction ?? throw new ArgumentNullException(nameof(costFunction));
        }

        public void Execute(Matrix<double> expectedOutputMatrix, Matrix<double> actualOutputMatrix, Matrix<double> costResult)
        {
            actualOutputMatrix.Map2(CostFunction.Apply, expectedOutputMatrix, costResult);
            RunningError += costResult.RowSums()[0];
        }
    }
}
