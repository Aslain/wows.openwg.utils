using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;

namespace OpenWG.Utils
{
    public enum WotClientBranch
    {
        Unknown = 0,
        Release = 1,
        CommonTest = 2,
        SuperTest = 3,
        Sandbox = 4
    }

    public enum WotClientType
    {
        Unknown = 0,
        SD = 1,
        HD = 2,
    }

    public enum WotClientRegion
    {
        Unknown = 0,
        CIS = 1,
        EU = 2,
        NA = 3,
        ASIA = 4,
        CN = 5
    }

    public class WotRegionIdRange
    {
        public long Min { get; }
        public long Max { get; }

        public WotRegionIdRange(long min, long max)
        {
            Min = min;
            Max = max;
        }
    }


    public class Wot
    {
        #region WOT::GetPreferredClientPath

        [DllImport(Constants.DllName_X86_32, EntryPoint = "WOT_GetPreferredClientPathW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetPreferredClientPathW_x86_32(StringBuilder buffer, Int32 bufferSize);

        [DllImport(Constants.DllName_X86_64, EntryPoint = "WOT_GetPreferredClientPathW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetPreferredClientPathW_x86_64(StringBuilder buffer, Int32 bufferSize);

        [DllImport(Constants.DllName_ARM_32, EntryPoint = "WOT_GetPreferredClientPathW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetPreferredClientPathW_ARM_32(StringBuilder buffer, Int32 bufferSize);

        [DllImport(Constants.DllName_ARM_64, EntryPoint = "WOT_GetPreferredClientPathW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetPreferredClientPathW_ARM_64(StringBuilder buffer, Int32 bufferSize);

        public static string GetPreferredClientPath()
        {
            var stringBuilder = new StringBuilder(Constants.MaxPathSize);

            switch (ProcessorArchitecture.GetProcessArchitecture())
            {
                case ProcessorArchitectureType.X86:
                    _GetPreferredClientPathW_x86_32(stringBuilder, Constants.MaxPathSize);
                    break;

                case ProcessorArchitectureType.X64:
                    _GetPreferredClientPathW_x86_64(stringBuilder, Constants.MaxPathSize);
                    break;

                case ProcessorArchitectureType.Arm:
                    _GetPreferredClientPathW_ARM_32(stringBuilder, Constants.MaxPathSize);
                    break;

                case ProcessorArchitectureType.Arm64:
                    _GetPreferredClientPathW_ARM_64(stringBuilder, Constants.MaxPathSize);
                    break;

                default:
                    throw new PlatformNotSupportedException();
            }

            return stringBuilder.ToString();
        }

        #endregion

        #region WOT::GetClientsCount

        [DllImport(Constants.DllName_X86_32, EntryPoint = "WOT_GetClientsCount", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _GetClientsCount_x86_32();

        [DllImport(Constants.DllName_X86_64, EntryPoint = "WOT_GetClientsCount", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _GetClientsCount_x86_64();

        [DllImport(Constants.DllName_ARM_32, EntryPoint = "WOT_GetClientsCount", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _GetClientsCount_ARM_32();

        [DllImport(Constants.DllName_ARM_64, EntryPoint = "WOT_GetClientsCount", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _GetClientsCount_ARM_64();

        public static long GetClientsCount()
        {
            switch (ProcessorArchitecture.GetProcessArchitecture())
            {
                case ProcessorArchitectureType.X86:
                    return _GetClientsCount_x86_32();

                case ProcessorArchitectureType.X64:
                    return _GetClientsCount_x86_64();

                case ProcessorArchitectureType.Arm:
                    return _GetClientsCount_ARM_32();

                case ProcessorArchitectureType.Arm64:
                    return _GetClientsCount_ARM_64();

                default:
                    throw new PlatformNotSupportedException();
            }

        }

        #endregion

        #region WOT::GetClientLocale

        [DllImport(Constants.DllName_X86_32, EntryPoint = "WOT_GetClientLocaleW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetClientLocaleW_x86_32(StringBuilder buffer, Int32 bufferSize, Int32 clientIndex);

        [DllImport(Constants.DllName_X86_64, EntryPoint = "WOT_GetClientLocaleW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetClientLocaleW_x86_64(StringBuilder buffer, Int32 bufferSize, Int32 clientIndex);

        [DllImport(Constants.DllName_ARM_32, EntryPoint = "WOT_GetClientLocaleW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetClientLocaleW_ARM_32(StringBuilder buffer, Int32 bufferSize, Int32 clientIndex);

        [DllImport(Constants.DllName_ARM_64, EntryPoint = "WOT_GetClientLocaleW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetClientLocaleW_ARM_64(StringBuilder buffer, Int32 bufferSize, Int32 clientIndex);

        public static string GetClientLocale(int clientIndex)
        {
            var stringBuilder = new StringBuilder(Constants.MaxPathSize);

            switch (ProcessorArchitecture.GetProcessArchitecture())
            {
                case ProcessorArchitectureType.X86:
                    _GetClientLocaleW_x86_32(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                case ProcessorArchitectureType.X64:
                    _GetClientLocaleW_x86_64(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                case ProcessorArchitectureType.Arm:
                    _GetClientLocaleW_ARM_32(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                case ProcessorArchitectureType.Arm64:
                    _GetClientLocaleW_ARM_64(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                default:
                    throw new PlatformNotSupportedException();
            }

            return stringBuilder.ToString();
        }

        #endregion

        #region WOT::GetClientPath

        [DllImport(Constants.DllName_X86_32, EntryPoint = "WOT_GetClientPathW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetClientPathW_x86_32(StringBuilder buffer, Int32 bufferSize, Int32 clientIndex);

        [DllImport(Constants.DllName_X86_64, EntryPoint = "WOT_GetClientPathW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetClientPathW_x86_64(StringBuilder buffer, Int32 bufferSize, Int32 clientIndex);

        [DllImport(Constants.DllName_ARM_32, EntryPoint = "WOT_GetClientPathW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetClientPathW_ARM_32(StringBuilder buffer, Int32 bufferSize, Int32 clientIndex);

        [DllImport(Constants.DllName_ARM_64, EntryPoint = "WOT_GetClientPathW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetClientPathW_ARM_64(StringBuilder buffer, Int32 bufferSize, Int32 clientIndex);

        public static string GetClientPath(int clientIndex)
        {
            var stringBuilder = new StringBuilder(Constants.MaxPathSize);

            switch (ProcessorArchitecture.GetProcessArchitecture())
            {
                case ProcessorArchitectureType.X86:
                    _GetClientPathW_x86_32(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                case ProcessorArchitectureType.X64:
                    _GetClientPathW_x86_64(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                case ProcessorArchitectureType.Arm:
                    _GetClientPathW_ARM_32(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                case ProcessorArchitectureType.Arm64:
                    _GetClientPathW_ARM_64(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                default:
                    throw new PlatformNotSupportedException();
            }

            return stringBuilder.ToString();
        }

        #endregion

        #region WOT::GetClientVersion

        [DllImport(Constants.DllName_X86_32, EntryPoint = "WOT_GetClientVersionW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void
            _GetClientVersionW_x86_32(StringBuilder buffer, Int32 bufferSize, Int32 clientIndex);

        [DllImport(Constants.DllName_X86_64, EntryPoint = "WOT_GetClientVersionW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void
            _GetClientVersionW_x86_64(StringBuilder buffer, Int32 bufferSize, Int32 clientIndex);

        [DllImport(Constants.DllName_ARM_32, EntryPoint = "WOT_GetClientVersionW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void
            _GetClientVersionW_ARM_32(StringBuilder buffer, Int32 bufferSize, Int32 clientIndex);

        [DllImport(Constants.DllName_ARM_64, EntryPoint = "WOT_GetClientVersionW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void
            _GetClientVersionW_ARM_64(StringBuilder buffer, Int32 bufferSize, Int32 clientIndex);

        public static Version GetClientVersion(int clientIndex)
        {
            var stringBuilder = new StringBuilder(Constants.MaxPathSize);

            switch (ProcessorArchitecture.GetProcessArchitecture())
            {
                case ProcessorArchitectureType.X86:
                    _GetClientVersionW_x86_32(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                case ProcessorArchitectureType.X64:
                    _GetClientVersionW_x86_64(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                case ProcessorArchitectureType.Arm:
                    _GetClientVersionW_ARM_32(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                case ProcessorArchitectureType.Arm64:
                    _GetClientVersionW_ARM_64(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                default:
                    throw new PlatformNotSupportedException();
            }

            if (stringBuilder.Length == 0)
            {
                throw new ArgumentException("Client index is invalid");
            }

            var verArray = stringBuilder.ToString().Split('.');
            if (verArray.Length != 4)
            {
                throw new InvalidDataException("Invalid client version");
            }

            return new Version(Convert.ToInt32(verArray[0]), Convert.ToInt32(verArray[1]), Convert.ToInt32(verArray[2]),
                Convert.ToInt32(verArray[3]));
        }

        #endregion

        #region WOT::GetClientExeVersion

        [DllImport(Constants.DllName_X86_32, EntryPoint = "WOT_GetClientExeVersionW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetClientExeVersionW_x86_32(StringBuilder buffer, Int32 bufferSize,
            Int32 clientIndex);

        [DllImport(Constants.DllName_X86_64, EntryPoint = "WOT_GetClientExeVersionW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetClientExeVersionW_x86_64(StringBuilder buffer, Int32 bufferSize,
            Int32 clientIndex);

        [DllImport(Constants.DllName_ARM_32, EntryPoint = "WOT_GetClientExeVersionW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetClientExeVersionW_ARM_32(StringBuilder buffer, Int32 bufferSize,
            Int32 clientIndex);

        [DllImport(Constants.DllName_ARM_64, EntryPoint = "WOT_GetClientExeVersionW", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern void _GetClientExeVersionW_ARM_64(StringBuilder buffer, Int32 bufferSize,
            Int32 clientIndex);

        public static Version GetClientExeVersion(int clientIndex)
        {
            var stringBuilder = new StringBuilder(Constants.MaxPathSize);

            switch (ProcessorArchitecture.GetProcessArchitecture())
            {
                case ProcessorArchitectureType.X86:
                    _GetClientExeVersionW_x86_32(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                case ProcessorArchitectureType.X64:
                    _GetClientExeVersionW_x86_64(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                case ProcessorArchitectureType.Arm:
                    _GetClientExeVersionW_ARM_32(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                case ProcessorArchitectureType.Arm64:
                    _GetClientExeVersionW_ARM_64(stringBuilder, Constants.MaxPathSize, clientIndex);
                    break;

                default:
                    throw new PlatformNotSupportedException();
            }

            if (stringBuilder.Length == 0)
            {
                throw new ArgumentException("Client index is invalid");
            }

            var verArray = stringBuilder.ToString().Split('.');
            if (verArray.Length != 4)
            {
                throw new InvalidDataException("Invalid client version");
            }

            return new Version(Convert.ToInt32(verArray[0]), Convert.ToInt32(verArray[1]), Convert.ToInt32(verArray[2]),
                Convert.ToInt32(verArray[3]));
        }

        #endregion

        #region WOT::GetClientBranch

        [DllImport(Constants.DllName_X86_32, EntryPoint = "WOT_GetClientBranch", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _GetClientBranch_x86_32(Int32 clientIndex);

        [DllImport(Constants.DllName_X86_64, EntryPoint = "WOT_GetClientBranch", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _GetClientBranch_x86_64(Int32 clientIndex);

        [DllImport(Constants.DllName_ARM_32, EntryPoint = "WOT_GetClientBranch", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _GetClientBranch_ARM_32(Int32 clientIndex);

        [DllImport(Constants.DllName_ARM_64, EntryPoint = "WOT_GetClientBranch", CharSet = CharSet.Unicode,CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _GetClientBranch_ARM_64(Int32 clientIndex);

        public static WotClientBranch GetClientBranch(int clientIndex)
        {
            Int32 result = 0;
            switch (ProcessorArchitecture.GetProcessArchitecture())
            {
                case ProcessorArchitectureType.X86:
                    result = _GetClientBranch_x86_32(clientIndex);
                    break;

                case ProcessorArchitectureType.X64:
                    result = _GetClientBranch_x86_64(clientIndex);
                    break;

                case ProcessorArchitectureType.Arm:
                    result = _GetClientBranch_ARM_32(clientIndex);
                    break;

                case ProcessorArchitectureType.Arm64:
                    result = _GetClientBranch_ARM_64(clientIndex);
                    break;

                default:
                    throw new PlatformNotSupportedException();
            }

            if (result < 0)
            {
                throw new ArgumentException("Invalid client id or client is corrupted");
            }

            return (WotClientBranch) result;

        }

        #endregion

        #region WOT::GetClientType

        [DllImport(Constants.DllName_X86_32, EntryPoint = "WOT_GetClientType", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _GetClientType_x86_32(Int32 clientIndex);

        [DllImport(Constants.DllName_X86_64, EntryPoint = "WOT_GetClientType", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _GetClientType_x86_64(Int32 clientIndex);

        [DllImport(Constants.DllName_ARM_32, EntryPoint = "WOT_GetClientType", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _GetClientType_ARM_32(Int32 clientIndex);

        [DllImport(Constants.DllName_ARM_64, EntryPoint = "WOT_GetClientType", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        private static extern Int32 _GetClientType_ARM_64(Int32 clientIndex);

        public static WotClientType GetClientType(int clientIndex)
        {
            Int32 result = 0;
            switch (ProcessorArchitecture.GetProcessArchitecture())
            {
                case ProcessorArchitectureType.X86:
                    result = _GetClientType_x86_32(clientIndex);
                    break;

                case ProcessorArchitectureType.X64:
                    result = _GetClientType_x86_64(clientIndex);
                    break;

                case ProcessorArchitectureType.Arm:
                    result = _GetClientType_ARM_32(clientIndex);
                    break;

                case ProcessorArchitectureType.Arm64:
                    result = _GetClientType_ARM_64(clientIndex);
                    break;

                default:
                    throw new PlatformNotSupportedException();
            }

            if (result < 0)
            {
                throw new ArgumentException("Invalid client id or client is corrupted");
            }

            return (WotClientType)result;

        }

        #endregion

        public static WotClientRegion GetRegionFromString(string regionName)
        {
            switch(regionName.ToUpper())
            {
                case "RU":
                case "CIS":
                    return WotClientRegion.CIS;
                case "EU":
                    return WotClientRegion.EU;
                case "NA":
                    return WotClientRegion.NA;
                case "ASIA":
                    return WotClientRegion.ASIA;
                case "CN":
                    return WotClientRegion.CN;
                default:
                    return WotClientRegion.Unknown;
            }
        }

        public static WotRegionIdRange GetIdsRangeForRegion(WotClientRegion region)
        {
            switch (region)
            {
                case WotClientRegion.CIS:
                    return new WotRegionIdRange(1L, 499999999L);

                case WotClientRegion.EU:
                    return new WotRegionIdRange(500000000L, 999999999L);

                case WotClientRegion.NA:
                    return new WotRegionIdRange(1000000000L, 1499999999L);

                case WotClientRegion.ASIA:
                    return new WotRegionIdRange(2000000000L, 3499999999L);

                default:
                    return new WotRegionIdRange(0L, 0L);

            }
        }
    }
}