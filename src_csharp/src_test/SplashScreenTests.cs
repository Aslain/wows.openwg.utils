using Xunit;

namespace XVM.Extensions.Tests
{
    public class SplashScreenTests
    {
        [Fact]
        public void ShowSplashScreen_1()
        {
            var result = SplashScreen.ShowSplashScreen("test.png", 2);
            Assert.True(result);
        }
    }
}
