using System;
using System.Runtime.InteropServices;

namespace XVM.Extensions
{
    public class Wine
    {

        #region Wine::IsRunningUnder

        [DllImport(Constants.DllName_X86_32, EntryPoint = "WINE_IsRunningUnder", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _IsRunningUnder_x86_32();

        [DllImport(Constants.DllName_X86_64, EntryPoint = "WINE_IsRunningUnder", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _IsRunningUnder_x86_64();
        
        [DllImport(Constants.DllName_ARM_32, EntryPoint = "WINE_IsRunningUnder", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _IsRunningUnder_ARM_32();

        [DllImport(Constants.DllName_ARM_64, EntryPoint = "WINE_IsRunningUnder", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _IsRunningUnder_ARM_64();

        public static bool IsRunningUnder()
        {
            switch (RuntimeInformation.ProcessArchitecture)
            {
                case Architecture.X86:
                    return _IsRunningUnder_x86_32();

                case Architecture.X64:
                    return _IsRunningUnder_x86_64();

                case Architecture.Arm:
                    return _IsRunningUnder_ARM_32();

                case Architecture.Arm64:
                    return _IsRunningUnder_ARM_64();

                default:
                    throw new PlatformNotSupportedException();
            }
        }

        #endregion
    }
}
