using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace QtNetCoreInterop
{
    public class QtNetCoreSession : IDisposable
    {
        readonly TaskCompletionSource<int> _finishHandler = new TaskCompletionSource<int>();
        readonly IntPtr _nativeEngine;
        readonly GCHandle _quitSignalHandle;

        [StructLayout(LayoutKind.Sequential)]
        struct InteropData
        {
            // ReSharper disable InconsistentNaming
            public IntPtr nativeEngine;
            public IntPtr signalCoreCLRInitiaizedCallback;
            public IntPtr setQuitSignal;
            // ReSharper restore InconsistentNaming
        }

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void CoreCLRInitializedCallbackDelegate(IntPtr nativeEngine, int result);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate int SetQuitSignalDelegate(IntPtr nativeEngine, IntPtr quitCallback);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void QuitSignalDelegate();

        public QtNetCoreSession(ref string[] args)
        {
            // the args contain an integer representing a pointer to our native engine
            // instance
            if (args.Length == 0)
                throw new InvalidOperationException("Args doesn't contain the integer pointer to the native engine.");

            if (!long.TryParse(args[args.Length - 1], out long pointer))
                throw new InvalidOperationException("The last arguement isn't a valid integer.");

            Console.WriteLine(args[args.Length - 1]);

            args = args.Take(args.Length - 1).ToArray(); // remove the trailing pointer

            var interopData = Marshal.PtrToStructure<InteropData>(new IntPtr(pointer));

            _nativeEngine = interopData.nativeEngine;

            QuitSignalDelegate quitSignal = QuitSignal;
            _quitSignalHandle = GCHandle.Alloc(quitSignal);
            Marshal.GetDelegateForFunctionPointer<SetQuitSignalDelegate>(interopData.setQuitSignal)
                (_nativeEngine, Marshal.GetFunctionPointerForDelegate(quitSignal));

            // let the c++ know we are all done and ready!
            Marshal.GetDelegateForFunctionPointer<CoreCLRInitializedCallbackDelegate>(interopData.signalCoreCLRInitiaizedCallback)
                (_nativeEngine, 0);
        }

        private void QuitSignal()
        {
            Console.WriteLine("C++ raised a signal kill. Setting result on TaskCompletionSource.");
            _finishHandler.SetResult(0);
        }

        public void WaitForExit()
        {
            _finishHandler.Task.Wait();
        }

        public void Dispose()
        {
        }
    }
}
