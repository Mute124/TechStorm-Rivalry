
using System.Diagnostics;
namespace TechStormDevTool
{

    class DevEnvironmentSetup
    {

      
        bool isGitInstalled = false;
        bool isMinGWInstalled = false;

        bool stayOpen = true;

        // Check if git is installed. Simply does git --version, if it doesnt go through well we know it isnt installed.
        private void CheckForGitAndInstall() {
            // Check if git is installed
            Operation operation = new Operation();


            int taskResult = operation.NewTask("git --version");
            
            if (taskResult == 0) {
                isGitInstalled = true;
            } else {
                isGitInstalled = false;
            }

            // if git is not installed, install it!
            if(this.isGitInstalled == false) {

                // use winget to install git
                Operation gitInstall = new Operation("winget install --id Git.Git -e --source winget");

            }
        }

        private void CheckForMinGW() {
            Operation minGWCheck = new Operation();

            
        }
        
        private void PrintHeader() {
            Console.WriteLine("--------------------------------Tech-Storm Dev Tools Installer----------------------------------");
            Console.WriteLine("| (1) Default Installation | (2) All but IDE | (3) Code + Compiler | (4) Just code | (5) Back  |");
            Console.WriteLine("------------------------------------------------------------------------------------------------");
        }

        
        public DevEnvironmentSetup()
        {

            
            PrintHeader();

            int installConfiguration = Console.Read();

            while (stayOpen) 
            {
                // Exit the loop
                if (installConfiguration == 5) {
                    break;
                }

                if (installConfiguration == 1) {
                    if (!this.isGitInstalled) {
                        CheckForGitAndInstall();
                    }
                } else if (installConfiguration == 2) {
                    if (!this.isGitInstalled) {
                        CheckForGitAndInstall();
                    }
                } 


            }

            





            // Install MinGW if not present.
            
        }
    }
}