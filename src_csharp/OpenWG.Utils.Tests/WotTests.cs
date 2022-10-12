using System;
using Xunit;

namespace OpenWG.Utils.Tests
{
    public class WotTests
    {
        [Fact]
        public void GetPreferredClientPath_1()
        {
            var clientPath = Wot.GetPreferredClientPath();

            Assert.NotNull(clientPath);
            Assert.NotEmpty(clientPath);
            Assert.Contains("World", clientPath);
        }

        [Fact]
        public void GetClientsCount_1()
        {
            var clientsCount = Wot.GetClientsCount();

            Assert.True(clientsCount>0);
        }

        [Fact]
        public void GetClientLocale_1()
        {
            var clientLocale = Wot.GetClientLocale(0);

            Assert.NotNull(clientLocale);
            Assert.NotEmpty(clientLocale);
            Assert.True(clientLocale.Length == 2);
        }

        [Fact]
        public void GetClientLocale_2()
        {
            var clientLocale = Wot.GetClientLocale(100000);

            Assert.NotNull(clientLocale);
            Assert.Empty(clientLocale);
        }

        [Fact]
        public void GetClientPath_1()
        {
            var clientPath = Wot.GetClientPath(0);

            Assert.NotNull(clientPath);
            Assert.NotEmpty(clientPath);
            Assert.Contains("World", clientPath);
        }

        [Fact]
        public void GetClientPath_2()
        {
            var clientPath = Wot.GetClientPath(100000);

            Assert.NotNull(clientPath);
            Assert.Empty(clientPath);
        }


        [Fact]
        public void GetClientVersion_1()
        {
            var clientVersion = Wot.GetClientVersion(0);

            Assert.NotNull(clientVersion);
            Assert.Equal(1,clientVersion.Major);
        }

        [Fact]
        public void GetClientVersion_2()
        {
            Assert.Throws<ArgumentException>(()=>
            {
               Wot.GetClientVersion(100000);
            });
        }


        [Fact]
        public void GetClientExeVersion_1()
        {
            var clientVersion = Wot.GetClientExeVersion(0);

            Assert.NotNull(clientVersion);
            Assert.Equal(1, clientVersion.Major);
        }

        [Fact]
        public void GetClientExeVersion_2()
        {
            Assert.Throws<ArgumentException>(() =>
            {
                Wot.GetClientExeVersion(100000);
            });
        }

        [Fact]
        public void GetClientBranch_1()
        {
            var clientBranch = Wot.GetClientBranch(0);

            Assert.NotEqual(WotClientBranch.Unknown, clientBranch);
        }

        [Fact]
        public void GetClientBranch_2()
        {
            Assert.Throws<ArgumentException>(() =>
            {
                Wot.GetClientBranch(100000);
            });
        }

        [Fact]
        public void GetClientType_1()
        {
            var clientBranch = Wot.GetClientType(0);

            Assert.NotEqual(WotClientType.Unknown, clientBranch);
        }

        [Fact]
        public void GetClientType_2()
        {
            Assert.Throws<ArgumentException>(() =>
            {
                Wot.GetClientType(100000);
            });
        }
    }
}