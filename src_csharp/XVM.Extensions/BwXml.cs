using System;
using System.Runtime.InteropServices;

namespace XVM.Extensions
{
    public class BwXml
    {
        #region BwXml::Unpack

        [DllImport(Constants.DllName_X86_32, EntryPoint = "BWXML_UnpackW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _Unpack_x86_32(string pathIn, string pathOut);

        [DllImport(Constants.DllName_X86_64, EntryPoint = "BWXML_UnpackW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _Unpack_x86_64(string pathIn, string pathOut);

        [DllImport(Constants.DllName_ARM_32, EntryPoint = "BWXML_UnpackW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _Unpack_ARM_32(string pathIn, string pathOut);

        [DllImport(Constants.DllName_ARM_64, EntryPoint = "BWXML_UnpackW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _Unpack_ARM_64(string pathIn, string pathOut);

        public static bool Unpack(string pathIn, string pathOut)
        {
            switch (ProcessorArchitecture.GetProcessArchitecture())
            {
                case ProcessorArchitectureType.X86:
                    return _Unpack_x86_32(pathIn, pathOut) >= 0;

                case ProcessorArchitectureType.X64:
                    return _Unpack_x86_64(pathIn, pathOut) >= 0;

                case ProcessorArchitectureType.Arm:
                    return _Unpack_ARM_32(pathIn, pathOut) >= 0;

                case ProcessorArchitectureType.Arm64:
                    return _Unpack_ARM_64(pathIn, pathOut) >= 0;

                default:
                    throw new PlatformNotSupportedException();
            }
        }

        #endregion
    }
}
