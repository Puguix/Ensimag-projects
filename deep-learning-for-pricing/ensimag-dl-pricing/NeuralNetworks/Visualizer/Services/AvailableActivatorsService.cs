using NeuralNetwork.Activators;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Visualizer.Services
{
    class AvailableActivatorsService
    {
        public List<ActivatorInfo> GetActivators()
        {
            return new List<ActivatorInfo>
            {
                new ActivatorInfo("Sigmoid", ActivatorType.Sigmoid),
                new ActivatorInfo("Identity", ActivatorType.Identity),
                new ActivatorInfo("Tanh", ActivatorType.Tanh),
                new ActivatorInfo("Leaky ReLU", ActivatorType.LeakyReLU)
            };
        }
    }
}
