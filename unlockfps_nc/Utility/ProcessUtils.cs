using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Reflection.PortableExecutable;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace unlockfps_nc.Utility
{
    internal class ProcessUtils
    {
        public static string GetProcessPath(IntPtr hProcess)
        {
            if (hProcess == IntPtr.Zero)
                return string.Empty;

            StringBuilder sb = new StringBuilder(1024);
            uint bufferSize = (uint)sb.Capacity;
            if (!Native.QueryFullProcessImageName(hProcess, 0, sb, ref bufferSize))
                return string.Empty;

            return sb.ToString();
        }

        public static IntPtr GetWindowFromProcessId(int processId)
        {
            IntPtr windowHandle = IntPtr.Zero;

            Native.EnumWindows((hWnd, lParam) =>
            {
                Native.GetWindowThreadProcessId(hWnd, out uint pid);
                if (pid == processId)
                {
                    windowHandle = hWnd;
                    return false;
                }

                return true;
            }, IntPtr.Zero);

            return windowHandle;
        }

        public static bool InjectDlls(IntPtr processHandle, List<string> dllPaths)
        {
#if !RELEASEMIN
            if (dllPaths.Count == 0)
                return true;

            Native.RtlAdjustPrivilege(20, true, false, out var _);

            var kernel32 = Native.LoadLibrary("kernel32.dll");
            var loadLibrary = Native.GetProcAddress(kernel32, "LoadLibraryW");

            var remoteVa = Native.VirtualAllocEx(processHandle, IntPtr.Zero, 0x1000,
                AllocationType.COMMIT | AllocationType.RESERVE, MemoryProtection.READWRITE);
            if (remoteVa == IntPtr.Zero)
                return false;

            foreach (var dllPath in dllPaths)
            {
                var nativeString = Marshal.StringToHGlobalUni(dllPath);
                var bytes = Encoding.Unicode.GetBytes(dllPath);
                Marshal.FreeHGlobal(nativeString);

                if (!Native.WriteProcessMemory(processHandle, remoteVa, bytes, bytes.Length, out var bytesWritten))
                    return false;

                var thread = Native.CreateRemoteThread(processHandle, IntPtr.Zero, 0, loadLibrary, remoteVa, 0, out var threadId);
                if (thread == IntPtr.Zero)
                    return false;

                Native.WaitForSingleObject(thread, uint.MaxValue);
                Native.CloseHandle(thread);
                Native.WriteProcessMemory(processHandle, remoteVa, new byte[bytes.Length], bytes.Length, out _);
            }

            Native.VirtualFreeEx(processHandle, remoteVa, 0, FreeType.RELEASE);
#endif
            return true;
        }

        public static unsafe IntPtr PatternScan(IntPtr module, string signature)
        {
            var (patternBytes, maskBytes) = ParseSignature(signature);

            var sizeOfImage = Native.GetModuleImageSize(module);
            var scanBytes = (byte*)module;

            if (Native.IsWine())
            {
                /*
                 *  Fixes a problem with LoadLibraryEx not working properly on Wine.
                 *  When the flag 'LOAD_LIBRARY_AS_IMAGE_RESOURCE' is used, it is supposed to map the entire file as READONLY.
                 *  But Wine maps each section with the respective protection, and if there is a section with no read permission, it will trigger Access Violation.
                */
                Native.VirtualProtect(module, sizeOfImage, MemoryProtection.EXECUTE_READWRITE, out _);
            }

            var span = new ReadOnlySpan<byte>(scanBytes, (int)sizeOfImage);
            var offset = PatternScan(span, patternBytes, maskBytes);

            if (offset != -1)
                return (IntPtr)(module.ToInt64() + offset);


            return IntPtr.Zero;
        }

        public static unsafe List<IntPtr> PatternScanAllOccurrences(IntPtr module, string signature)
        {
            var (patternBytes, maskBytes) = ParseSignature(signature);

            var sizeOfImage = Native.GetModuleImageSize(module);
            var scanBytes = (byte*)module;

            if (Native.IsWine())
                Native.VirtualProtect(module, sizeOfImage, MemoryProtection.EXECUTE_READWRITE, out _);
            
            var span = new ReadOnlySpan<byte>(scanBytes, (int)sizeOfImage);
            var offsets = new List<IntPtr>();

            var totalProcessed = 0L;
            while (true)
            {
                var offset = PatternScan(span, patternBytes, maskBytes);
                if (offset == -1)
                    break;

                offsets.Add((IntPtr)(module.ToInt64() + offset + totalProcessed));

                var processedOffset = offset + patternBytes.Length;
                totalProcessed += processedOffset;

                span = span.Slice((int)processedOffset);
            }

            return offsets;
        }

        public static long PatternScan(ReadOnlySpan<byte> data, byte[] patternBytes, bool[] maskBytes)
        {
            var s = patternBytes.Length;
            var d = patternBytes;

            for (var i = 0; i < data.Length - s; i++)
            {
                var found = true;
                for (var j = 0; j < s; j++)
                {
                    if (d[j] != data[i + j] && !maskBytes[j])
                    {
                        found = false;
                        break;
                    }
                }

                if (found)
                    return i;
            }

            return -1;
        }

        private static (byte[], bool[]) ParseSignature(string signature)
        {
            var tokens = signature.Split(' ');
            var patternBytes = tokens
                .Select(x => x == "?" ? (byte)0xFF : Convert.ToByte(x, 16))
                .ToArray();
            var maskBytes = tokens
                .Select(x => x == "?")
                .ToArray();

            return (patternBytes, maskBytes);
        }

        public static IntPtr GetModuleBase(IntPtr hProcess, string moduleName)
        {
            var moduleNameLower = moduleName.ToLowerInvariant();
            var modules = new IntPtr[1024];

            if (!Native.EnumProcessModulesEx(hProcess, modules, (uint)(modules.Length * IntPtr.Size), out var bytesNeeded, 2))
            {
                var errorCode = Marshal.GetLastWin32Error();
                if (errorCode != 299)
                {
                    MessageBox.Show($@"EnumProcessModulesEx failed ({errorCode}){Environment.NewLine}{Marshal.GetLastPInvokeErrorMessage()}"
                        , @"Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return IntPtr.Zero;
                }
            }

            foreach (var module in modules.Where(x => x != IntPtr.Zero))
            {
                StringBuilder sb = new StringBuilder(1024);
                if (Native.GetModuleBaseName(hProcess, module, sb, (uint)sb.Capacity) == 0)
                    continue;

                if (sb.ToString().ToLowerInvariant() != moduleNameLower)
                    continue;

                if (!Native.GetModuleInformation(hProcess, module, out var moduleInfo, (uint)Marshal.SizeOf<MODULEINFO>()))
                    continue;

                return moduleInfo.lpBaseOfDll;
            }

            return IntPtr.Zero;
        }

        public static bool IsWindowDrawing(IntPtr hWnd)
        {
            if (!Native.IsWindowVisible(hWnd))
                return false;

            Native.RedrawWindow(hWnd, IntPtr.Zero, IntPtr.Zero, 0x122); // RDW_INTERNALPAINT | RDW_NOERASE | RDW_UPDATENOW
            Native.UpdateWindow(hWnd);

            var hdc = Native.GetDC(hWnd);
            if (hdc == IntPtr.Zero)
                return false;

            Native.ReleaseDC(hWnd, hdc);
            return true;
        }

    }
}
