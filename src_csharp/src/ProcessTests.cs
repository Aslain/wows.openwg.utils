using System.Threading;
using Xunit;

namespace XVM.Extensions.Tests
{
    public class ProcessTests
    {
        [Fact]
        public void GetRunningInDirectory_1()
        {
            var result = Process.GetRunningInDirectory("C:\\Windows\\");
            Assert.NotNull(result);
            Assert.NotEmpty(result);
            Assert.Contains("explorer.exe", result);
        }

        [Fact]
        public void GetRunningInDirectory_2()
        {
            var result = Process.GetRunningInDirectory("C:\\Wondows\\");
            Assert.NotNull(result);
            Assert.Empty(result);
        }

        [Fact]
        public void TerminateProcess_1()
        {
            System.Diagnostics.Process.Start("calc.exe");
            Thread.Sleep(10000);
            var result = Process.TerminateProcess("calc");
            Assert.True(result);
        }

        [Fact]
        public void TerminateProcess_2()
        {
            var result = Process.TerminateProcess("cooooolc.exe");
            Assert.False(result);
        }

    }
}
