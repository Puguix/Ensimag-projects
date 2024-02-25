using NeuralNetwork.Activators;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Visualizer.Services
{
    class ActivatorInfo
    {
        public ActivatorInfo(string name, ActivatorType activator)
        {
            Name = name;
            Activator = activator;
        }

        public string Name { get; }
        public ActivatorType Activator { get; }

    }
}
