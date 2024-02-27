
using System.Diagnostics;

namespace TechStormDevTool {

    // Use only for one time operations. Also kinda slow.
    class Operation {


        
        public void ClearScreen() {
            Operation operation = new Operation("clear");

        }

        // Does something in CMD. and returns it's exit code
        public int NewTask(String task) {
            Console.WriteLine("Executing command : " + task);

            // Create a new Process object.
            Process process = new Process();        // Set the StartInfo.FileName property to the path of the CMD executable.
            process.StartInfo.FileName = "cmd.exe";        // Set the StartInfo.Arguments property to the CMD command that you want to execute.
            process.StartInfo.Arguments = "/c " + task;        // Start the process.
            process.Start();        // Wait for the process to finish.
            process.WaitForExit();        // Read the output of the process.

            return process.ExitCode;
            
        }

        // just does something but doesnt return
        public Operation(String task) {
            Console.WriteLine("Executing command : " + task);

            // Create a new Process object.
            Process process = new Process();        // Set the StartInfo.FileName property to the path of the CMD executable.
            process.StartInfo.FileName = "cmd.exe";        // Set the StartInfo.Arguments property to the CMD command that you want to execute.
            process.StartInfo.Arguments = "/c " + task;        // Start the process.
            process.Start();        // Wait for the process to finish.
            process.WaitForExit();        // Read the output of the process.

        }

        public Operation() {

        }
    }
}