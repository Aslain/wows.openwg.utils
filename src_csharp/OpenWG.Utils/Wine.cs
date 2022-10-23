// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

using System;
using System.Runtime.InteropServices;

namespace OpenWG.Utils
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
            switch (ProcessorArchitecture.GetProcessArchitecture())
            {
                case ProcessorArchitectureType.X86:
                    return _IsRunningUnder_x86_32();

                case ProcessorArchitectureType.X64:
                    return _IsRunningUnder_x86_64();

                case ProcessorArchitectureType.Arm:
                    return _IsRunningUnder_ARM_32();

                case ProcessorArchitectureType.Arm64:
                    return _IsRunningUnder_ARM_64();

                default:
                    throw new PlatformNotSupportedException();
            }
        }

        #endregion
    }
}
