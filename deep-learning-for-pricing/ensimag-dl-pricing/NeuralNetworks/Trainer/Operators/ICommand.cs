using MathNet.Numerics.LinearAlgebra;
using System;
using System.Collections.Generic;
using System.Text;

namespace Trainer.Operators
{
    internal interface ICommand
    {
        void Execute(Matrix<double> expectedOutputMatrix, Matrix<double> actualOutputMatrix, Matrix<double> costResult);
    }
}
