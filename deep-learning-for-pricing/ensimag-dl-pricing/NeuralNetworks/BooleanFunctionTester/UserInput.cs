using Prism.Mvvm;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace BooleanFunctionTester
{
    internal class UserInput : BindableBase
    {
        private double firstArgument;
        private double secondArgument;

        public double FirstArgument
        {
            get => firstArgument;
            set => SetProperty(ref firstArgument, value);
        }

        public double SecondArgument
        {
            get => secondArgument;
            set => SetProperty(ref secondArgument, value);
        }

        public UserInput()
        {
            FirstArgument = 0;
            SecondArgument = 0;
        }
    }
}
