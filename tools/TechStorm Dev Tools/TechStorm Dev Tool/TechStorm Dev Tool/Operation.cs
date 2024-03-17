using System.Diagnostics;

namespace TechStorm_Dev_Tool
{
    // Use only for one time operations. Also kinda slow.
    public class Operation
    {
        #region Public Constructors

        // just does something but doesnt return
        public Operation(string task)
        {
            Console.WriteLine("Executing command : " + task);

            // Create a new Process object.
            Process process = new Process();        // Set the StartInfo.FileName property to the path of the CMD executable.
            process.StartInfo.FileName = "cmd.exe";        // Set the StartInfo.Arguments property to the CMD command that you want to execute.
            process.StartInfo.Arguments = "/c " + task;        // Start the process.
            process.Start();        // Wait for the process to finish.
            process.WaitForExit();        // Read the output of the process.
        }

        public Operation()
        {
        }

        #endregion Public Constructors

        #region Public Methods

        public void ClearScreen()
        {
            Operation operation = new Operation("clear");
        }

        // Does something in CMD. and returns it's exit code
        public int NewTask(string task)
        {
            Console.WriteLine("Executing command : " + task);

            // Create a new Process object.
            Process process = new Process();        // Set the StartInfo.FileName property to the path of the CMD executable.
            process.StartInfo.FileName = "cmd.exe";        // Set the StartInfo.Arguments property to the CMD command that you want to execute.
            process.StartInfo.Arguments = "/c " + task;        // Start the process.
            process.Start();        // Wait for the process to finish.
            process.WaitForExit();        // Read the output of the process.

            return process.ExitCode;
        }

        #endregion Public Methods
    }
}
