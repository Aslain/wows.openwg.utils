using System;
using System.Runtime.InteropServices;
using System.Text;

namespace XVM.Extensions
{
    public class WGC
    {
        #region WGC::GetInstallPath

        [DllImport(Constants.DllName_X86_32, EntryPoint = "WGC_GetInstallPathW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetInstallPathW_x86_32(StringBuilder buffer, Int32 bufferSize);

        [DllImport(Constants.DllName_X86_64, EntryPoint = "WGC_GetInstallPathW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetInstallPathW_x86_64(StringBuilder buffer, Int32 bufferSize);

        [DllImport(Constants.DllName_ARM_32, EntryPoint = "WGC_GetInstallPathW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetInstallPathW_ARM_32(StringBuilder buffer, Int32 bufferSize);

        [DllImport(Constants.DllName_ARM_64, EntryPoint = "WGC_GetInstallPathW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetInstallPathW_ARM_64(StringBuilder buffer, Int32 bufferSize);

        public static string GetInstallPath()
        {
            var stringBuilder = new StringBuilder(Constants.MaxPathSize);

            switch (ProcessorArchitecture.GetProcessArchitecture())
            {
                case ProcessorArchitectureType.X86:
                    _GetInstallPathW_x86_32(stringBuilder, Constants.MaxPathSize);
                    break;

                case ProcessorArchitectureType.X64:
                    _GetInstallPathW_x86_64(stringBuilder, Constants.MaxPathSize);
                    break;

                case ProcessorArchitectureType.Arm:
                    _GetInstallPathW_ARM_32(stringBuilder, Constants.MaxPathSize);
                    break;

                case ProcessorArchitectureType.Arm64:
                    _GetInstallPathW_ARM_64(stringBuilder, Constants.MaxPathSize);
                    break;

                default:
                    throw new PlatformNotSupportedException();
            }

            return stringBuilder.ToString();
        }

        #endregion

        #region WGC::IsInstalled

        [DllImport(Constants.DllName_X86_32, EntryPoint = "WGC_IsInstalled", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _IsInstalled_x86_32();

        [DllImport(Constants.DllName_X86_64, EntryPoint = "WGC_IsInstalled", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _IsInstalled_x86_64();

        [DllImport(Constants.DllName_ARM_32, EntryPoint = "WGC_IsInstalled", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _IsInstalled_ARM_32();

        [DllImport(Constants.DllName_ARM_64, EntryPoint = "WGC_IsInstalled", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _IsInstalled_ARM_64();

        public static bool IsInstalled()
        {
            switch (ProcessorArchitecture.GetProcessArchitecture())
            {
                case ProcessorArchitectureType.X86:
                    return _IsInstalled_x86_32();

                case ProcessorArchitectureType.X64:
                    return _IsInstalled_x86_64();

                case ProcessorArchitectureType.Arm:
                    return _IsInstalled_ARM_32();

                case ProcessorArchitectureType.Arm64:
                    return _IsInstalled_ARM_64();

                default:
                    throw new PlatformNotSupportedException();
            }
        }

        #endregion
    }
}
