using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TechStorm_Dev_Tool
{
    public abstract class Tool
    {
        #region Public Methods

        public virtual void init()
        {
            // Console.WriteLine("Starting " + toolName + "...");
        }

        public virtual void Update()
        {
        }

        #endregion Public Methods
    }
}
