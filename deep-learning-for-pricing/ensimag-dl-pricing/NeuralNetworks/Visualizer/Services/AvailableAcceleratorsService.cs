using NeuralNetwork.GradientAccelerators;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Visualizer.Configuration.GradientAccelerators;

namespace Visualizer.Services
{
    class AvailableAcceleratorsService
    {
        public List<AcceleratorInfo> GetAccelerators()
        {
            return new List<AcceleratorInfo>
            {
                new AcceleratorInfo("None", new NoAcceleratorConfigViewModel()),
                new AcceleratorInfo("Adam", new AdamConfigViewModel())
            };
        }
    }
}
