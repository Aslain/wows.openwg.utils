using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace XVM.Extensions
{
    public class SplashScreen
    {
        #region SplashScreen::ShowSplashScreen

        [DllImport(Constants.DllName_X86_32, EntryPoint = "SPLASHSCREEN_ShowSplashScreenW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _ShowSplashScreen_x86_32(string filePath, Int32 secondsToShow);

        [DllImport(Constants.DllName_X86_64, EntryPoint = "SPLASHSCREEN_ShowSplashScreenW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _ShowSplashScreen_x86_64(string filePath, Int32 secondsToShow);

        [DllImport(Constants.DllName_ARM_32, EntryPoint = "SPLASHSCREEN_ShowSplashScreenW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _ShowSplashScreen_ARM_32(string filePath, Int32 secondsToShow);

        [DllImport(Constants.DllName_ARM_64, EntryPoint = "SPLASHSCREEN_ShowSplashScreenW", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern bool _ShowSplashScreen_ARM_64(string filePath, Int32 secondsToShow);


        public static bool ShowSplashScreen(string filePath, int secondsToShow)
        {
            switch (ProcessorArchitecture.GetProcessArchitecture())
            {
                case ProcessorArchitectureType.X86:
                    return _ShowSplashScreen_x86_32(filePath, secondsToShow);

                case ProcessorArchitectureType.X64:
                    return _ShowSplashScreen_x86_64(filePath, secondsToShow);

                case ProcessorArchitectureType.Arm:
                    return _ShowSplashScreen_ARM_32(filePath, secondsToShow);

                case ProcessorArchitectureType.Arm64:
                    return _ShowSplashScreen_ARM_64(filePath, secondsToShow);

                default:
                    throw new PlatformNotSupportedException();
            }
        }

        #endregion
    }
}
