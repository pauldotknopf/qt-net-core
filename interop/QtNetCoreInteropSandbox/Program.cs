using System;

namespace QtNetCoreInteropSandbox
{
    public static class TestClass
    {
        public static void TestStaticMethod()
        {
            Console.WriteLine("Invoked static method!!");
        }
    }

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