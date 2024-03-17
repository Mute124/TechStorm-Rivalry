namespace PackageManager
{
    public enum ECommands
    {
        ECOMMAND_INSTALL_PKG
    };

    public class PackageManager : TechStorm_Dev_Tool.Tool
    {
        #region Public Methods

        public override void init()
        {
            base.init();
            bool exit = false;
            Console.Write("Hello there, How may I be of use? : ");

            String mode = Console.ReadLine().ToLower();
            Console.WriteLine();
            while (!exit)
            {
                switch (mode)
                {
                    case "install pkg":
                        break;

                    default:
                        Console.WriteLine("I do not understand what you mean by " + mode + ", please reinput command and try again");
                        break;
                }
            }
        }

        #endregion Public Methods
    }
}
