using Xunit;

namespace XVM.Extensions.Tests
{
    public class WineTests
    {
        [Fact(Skip = "Broken")]
        public void IsRunningUnder_1()
        {
            var underWine = Wine.IsRunningUnder();

            Assert.False(underWine);
        }
    }
}