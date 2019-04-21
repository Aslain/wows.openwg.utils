using System;
using Xunit;

namespace XVM.Extensions.Tests
{
    public class XvmTests
    {
        [Fact]
        public void GetLatestVersion_1()
        {
            var xvm = new XVM();
            var version = xvm.GetLatestVersion(WotClientRegion.CIS).Result;
        }
    }
}