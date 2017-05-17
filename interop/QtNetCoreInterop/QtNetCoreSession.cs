using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace QtNetCoreInterop
{
    public class QtNetCoreSession : IDisposable
    {
        readonly TaskCompletionSource<int> _finishHandler = new TaskCompletionSource<int>();
        readonly IntPtr _nativeEngine;
        readonly GCHandle _quitSignalHandle;
        readonly GCHandle _invokeStaticHandle;

        [StructLayout(LayoutKind.Sequential)]
        struct InteropData
        {
            // ReSharper disable InconsistentNaming
            public IntPtr nativeEngine;
            public IntPtr signalCoreCLRInitiaizedCallback;
            public IntPtr setDelegates;
            // ReSharper restore InconsistentNaming
        }

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void CoreCLRInitializedCallbackDelegate(IntPtr nativeEngine, int result);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate int SetDelegatesDelegate(IntPtr nativeEngine, IntPtr quitCallback, IntPtr invokeStatic);

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate void QuitSignalDelegate();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        delegate IntPtr InvokeStaticDelegate([MarshalAs(UnmanagedType.LPStr)]string type, [MarshalAs(UnmanagedType.LPStr)]string method);

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
            
            InvokeStaticDelegate invokeStatic = InvokeStatic;
            _invokeStaticHandle = GCHandle.Alloc(invokeStatic);

            // send all our delegates to c++
            Marshal.GetDelegateForFunctionPointer<SetDelegatesDelegate>(interopData.setDelegates)(
                _nativeEngine,
                Marshal.GetFunctionPointerForDelegate(quitSignal),
                Marshal.GetFunctionPointerForDelegate(invokeStatic));

            // let the c++ know we are all done and ready!
            Marshal.GetDelegateForFunctionPointer<CoreCLRInitializedCallbackDelegate>(interopData.signalCoreCLRInitiaizedCallback)
                (_nativeEngine, 0);
        }

        private void QuitSignal()
        {
            Console.WriteLine("C++ raised a signal kill. Setting result on TaskCompletionSource.");
            _finishHandler.SetResult(0);
        }

        private IntPtr InvokeStatic(string type, string method)
        {
            var typeInfo = Type.GetType(type);
            var methodInfo = typeInfo.GetMethod(method, BindingFlags.Static | BindingFlags.Public);
            methodInfo.Invoke(null, new object[0]);
            return IntPtr.Zero;
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
