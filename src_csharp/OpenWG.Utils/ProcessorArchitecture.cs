using System;
using System.Runtime.InteropServices;

namespace OpenWG.Utils
{
    /// <summary>Indicates the processor ProcessorArchitectureType. </summary>
    public enum ProcessorArchitectureType : short
    {
        X86     = 0,
        Arm     = 5,
        IA64    = 6,
        X64     = 9,
        Arm64   = 12,
        Unknown = 0xFF
    }

    internal class ProcessorArchitecture {

        [DllImport("kernel32.dll")]
        private static extern void GetNativeSystemInfo(ref SYSTEM_INFO lpSystemInfo);

        [StructLayout(LayoutKind.Sequential)]
        private struct SYSTEM_INFO
        {
            public short wProcessorArchitecture;
            public short wReserved;
            public int dwPageSize;
            public IntPtr lpMinimumApplicationAddress;
            public IntPtr lpMaximumApplicationAddress;
            public IntPtr dwActiveProcessorMask;
            public int dwNumberOfProcessors;
            public int dwProcessorType;
            public int dwAllocationGranularity;
            public short wProcessorLevel;
            public short wProcessorRevision;
        }

        public static ProcessorArchitectureType GetProcessorArchitecture()
        {
            SYSTEM_INFO si = new SYSTEM_INFO();
            GetNativeSystemInfo(ref si);
            return (ProcessorArchitectureType)si.wProcessorArchitecture;
        }

        public static ProcessorArchitectureType GetProcessArchitecture()
        {
            var arch = GetProcessorArchitecture();
            if (!Environment.Is64BitProcess)
            {
                switch (arch)
                {
                    case ProcessorArchitectureType.X64:
                        return ProcessorArchitectureType.X86;
                    case ProcessorArchitectureType.Arm64:
                        return ProcessorArchitectureType.Arm;
                    default:
                        break;
                }
            }

            return arch;
        }
    }
}