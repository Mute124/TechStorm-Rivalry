using System.Diagnostics;

namespace TechStorm_Dev_Tool
{
    // Cmd manager. gets given commands that it then passes into the cmd variable.
    public class CMDMan
    {
        #region Public Methods

        public void NewTask(string task)
        {
            if (shouldLog)
            {
                Console.WriteLine("Executing command : " + task);

                cmd.StartInfo.Arguments = "/c " + task;        // Start the process.
                cmd.Start();        // Wait for the process to finish.
                cmd.WaitForExit();        // Read the output of the process.
            }
            else
            {
                cmd.StartInfo.Arguments = "/c " + task;        // Start the process.
                cmd.Start();        // Wait for the process to finish.
            }

            cmd.StartInfo.Arguments = "";
        }

        #endregion Public Methods

        #region Private Fields

        private Process cmd;
        private bool shouldLog;

        #endregion Private Fields

        #region Private Constructors

        private CMDMan(bool enableLogging)
        {
            shouldLog = enableLogging;

            CreateCMD();
        }

        #endregion Private Constructors

        #region Private Methods

        private void CreateCMD()
        {
            if (shouldLog)
            {
                Console.WriteLine("Starting CMD...");
                cmd = new Process();
                cmd.StartInfo.FileName = "cmd.exe";

                Console.WriteLine("CMD started");
            }
        }

        #endregion Private Methods
    }
}
