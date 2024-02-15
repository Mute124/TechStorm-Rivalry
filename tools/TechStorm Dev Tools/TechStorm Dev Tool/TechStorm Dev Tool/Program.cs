// See https://aka.ms/new-console-template for more information

using System;


namespace TechStormDevTool
{
    class Program
    {
        
        bool isFirstTime;
        static void PrintHeader() {
            Console.WriteLine("--------------------------------Tech-Storm Dev Tools--------------------------------------------");
            Console.WriteLine("| (1)  |");
            Console.WriteLine("------------------------------------------------------------------------------------------------");
        }

        static void Main(string[] args)
        {            
            // Setup Dev env. TODO: If already set up, skip this step.
            DevEnvironmentSetup environmentSetup = new DevEnvironmentSetup();

            PrintHeader();
            bool stayOpen = true;

            while(stayOpen) {
                String usrInput = Console.ReadLine();
                if (usrInput.Equals("q")) {
                    stayOpen = false;
                }
            }

            

        }
    }
}