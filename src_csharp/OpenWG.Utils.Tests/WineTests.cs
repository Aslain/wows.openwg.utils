// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

using Xunit;

namespace OpenWG.Utils.Tests
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