using Xunit;

namespace XVM.Extensions.Tests
{
    public class WGCTests
    {
        [Fact]
        public void GetInstallPath_1()
        {
            var wgcPath = WGC.GetInstallPath();

            Assert.NotNull(wgcPath);
            Assert.NotEmpty(wgcPath);
            Assert.Contains(@":\", wgcPath);
            Assert.Contains("Wargaming", wgcPath);
        }

        [Fact]
        public void IsInstalled_1()
        {
            var isInstalled = WGC.IsInstalled();

            Assert.True(isInstalled);
        }
    }
}