// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace OpenWG.Utils
{
    public class Process
    {
        #region Process::GetRunningInDirectory

        [DllImport(Constants.DllName_X86_32, EntryPoint = "PROCESS_GetRunningInDirectoryW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _GetRunningInDirectoryW_x86_32(string directoryPath, StringBuilder outputList, Int32 outputListSize);

        [DllImport(Constants.DllName_X86_64, EntryPoint = "PROCESS_GetRunningInDirectoryW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _GetRunningInDirectoryW_x86_64(string directoryPath, StringBuilder outputList, Int32 outputListSize);

        [DllImport(Constants.DllName_ARM_32, EntryPoint = "PROCESS_GetRunningInDirectoryW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _GetRunningInDirectoryW_ARM_32(string directoryPath, StringBuilder outputList, Int32 outputListSize);

        [DllImport(Constants.DllName_ARM_64, EntryPoint = "PROCESS_GetRunningInDirectoryW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _GetRunningInDirectoryW_ARM_64(string directoryPath, StringBuilder outputList, Int32 outputListSize);


        public static List<string> GetRunningInDirectory(string directoryPath)
        {
            int bufferSize = 65535;
            var stringBuilder = new StringBuilder(bufferSize);


            switch (ProcessorArchitecture.GetProcessArchitecture())
            {
                case ProcessorArchitectureType.X86:
                    _GetRunningInDirectoryW_x86_32(directoryPath, stringBuilder, bufferSize);
                    break;

                case ProcessorArchitectureType.X64:
                    _GetRunningInDirectoryW_x86_64(directoryPath, stringBuilder, bufferSize);
                    break;

                case ProcessorArchitectureType.Arm:
                    _GetRunningInDirectoryW_ARM_32(directoryPath, stringBuilder, bufferSize);
                    break;
                case ProcessorArchitectureType.Arm64:
                    _GetRunningInDirectoryW_ARM_64(directoryPath, stringBuilder, bufferSize);
                    break;

                default:
                    throw new PlatformNotSupportedException();
            }

            return stringBuilder.Length==0 ? new List<string>() : stringBuilder.ToString().Split(';').Distinct().ToList();
        }

        #endregion

        #region Process::TerminateProcess

        [DllImport(Constants.DllName_X86_32, EntryPoint = "PROCESS_TerminateProcess", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _TerminateProcess_x86_32(string processName);

        [DllImport(Constants.DllName_X86_64, EntryPoint = "PROCESS_TerminateProcess", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _TerminateProcess_x86_64(string processName);

        [DllImport(Constants.DllName_ARM_32, EntryPoint = "PROCESS_TerminateProcess", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _TerminateProcess_ARM_32(string processName);

        [DllImport(Constants.DllName_ARM_64, EntryPoint = "PROCESS_TerminateProcess", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _TerminateProcess_ARM_64(string processName);


        public static bool TerminateProcess(string processName)
        {
            switch (ProcessorArchitecture.GetProcessArchitecture())
            {
                case ProcessorArchitectureType.X86:
                    return _TerminateProcess_x86_32(processName);

                case ProcessorArchitectureType.X64:
                    return _TerminateProcess_x86_64(processName);

                case ProcessorArchitectureType.Arm:
                    return _TerminateProcess_ARM_32(processName);

                case ProcessorArchitectureType.Arm64:
                    return _TerminateProcess_ARM_64(processName);

                default:
                    throw new PlatformNotSupportedException();
            }
        }

        #endregion
    }
}
