// See https://aka.ms/new-console-template for more information

namespace TechStorm_Dev_Tool
{
    public class Program
    {
        #region Private Fields

        private bool isFirstTime;

        #endregion Private Fields

        #region Private Methods

        public static void Main(string[] args)
        {
            // Setup Dev env. TODO: If already set up, skip this step.
            DevEnvironmentSetup environmentSetup = new DevEnvironmentSetup();

            PrintHeader();
            bool stayOpen = true;

            while (stayOpen)
            {
                string usrInput = Console.ReadLine();
                if (usrInput.Equals("q"))
                {
                    stayOpen = false;
                }
            }
        }

        private static void PrintHeader()
        {
            Console.WriteLine("--------------------------------Tech-Storm Dev Tools--------------------------------------------");
            Console.WriteLine("| (1) Export | (2) Package Manager |");
            Console.WriteLine("------------------------------------------------------------------------------------------------");
        }

        #endregion Private Methods
    }
}
