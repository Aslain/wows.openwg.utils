using System.Threading;
using Xunit;

namespace XVM.Extensions.Tests
{
    public class SplashScreenTests
    {
        [Fact]
        public void ShowSplashScreen_1()
        {
            var result = SplashScreen.ShowSplashScreen("assets/splashscreen.png", 1);
            Assert.True(result);
        }

        [Fact]
        public void ShowSplashScreen_2()
        {
            var result = SplashScreen.ShowSplashScreen("assets/splashscreen.bmp", 1);
            Assert.True(result);
        }


        [Fact]
        public void ShowSplashScreen_3()
        {
            Assert.False(SplashScreen.ShowSplashScreen("assets/nonexistent.bmp", 1));
        }
    }
}
