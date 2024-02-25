using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TrainingConsole
{
    internal class ErrorSummary
    {
        public ErrorSummary(int epochNb, double trainingError, double validationError)
        {
            EpochNb = epochNb;
            TrainingError = trainingError;
            ValidationError = validationError;
        }

        public int EpochNb { get; }
        public double TrainingError { get; }
        public double ValidationError { get; }
    }
}
