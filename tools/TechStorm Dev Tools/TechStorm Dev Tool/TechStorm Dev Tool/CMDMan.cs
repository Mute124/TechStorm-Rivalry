using System.Diagnostics;

namespace TechStormDevTool
{
    // Cmd manager. gets given commands that it then passes into the cmd variable.
    public class CMDMan {
        bool shouldLog;
        private Process cmd;

        public void NewTask(String task) {
            if (shouldLog) {
                Console.WriteLine("Executing command : " + task);

                this.cmd.StartInfo.Arguments = "/c " + task;        // Start the process.
                this.cmd.Start();        // Wait for the process to finish.
                this.cmd.WaitForExit();        // Read the output of the process.
            } else {
                this.cmd.StartInfo.Arguments = "/c " + task;        // Start the process.
                this.cmd.Start();        // Wait for the process to finish.
            }

            this.cmd.StartInfo.Arguments = "";
        }

        private void CreateCMD() {
            if (shouldLog) {
                Console.WriteLine("Starting CMD...");
                cmd = new Process();
                cmd.StartInfo.FileName = "cmd.exe";

                Console.WriteLine("CMD started");
            }
        }

        CMDMan(bool enableLogging) {
            shouldLog = enableLogging;

            CreateCMD();

        }
    }
}