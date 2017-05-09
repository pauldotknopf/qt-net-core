using System;

namespace QtNetCoreInteropSandbox
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Entered Program.Main, in the CoreCLR...");

            using (var session = new QtNetCoreInterop.QtNetCoreSession(ref args))
            {
                Console.WriteLine("Waiting for the kill signal from c++...");
                session.WaitForExit();
            }

            Console.WriteLine("Leaving CoreCLR now...");
        }
    }
}