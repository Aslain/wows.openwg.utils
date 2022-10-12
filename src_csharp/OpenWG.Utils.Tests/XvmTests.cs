using System;
using Xunit;

namespace OpenWG.Utils.Tests
{
    public class XvmTests
    {
        [Fact(Skip = "Broken")]
        public void GetLatestVersion_1()
        {
            var xvm = new XVM();
            var version = xvm.GetLatestVersion(WotClientRegion.CIS).Result;
        }
    }
}