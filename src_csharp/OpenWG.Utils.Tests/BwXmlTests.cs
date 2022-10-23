// SPDX-License-Identifier: MIT
// Copyright (c) 2017-2022 OpenWG.Utils Contributors

using System;
using System.Collections.Generic;
using System.Text;
using System.Xml.Linq;
using Xunit;

namespace OpenWG.Utils.Tests
{
    public class BwXmlTests
    {
        [Fact]
        public void Unpack_1()
        {
            Assert.False(BwXml.Unpack(null,null));
        }

        [Fact]
        public void Unpack_2()
        {
            Assert.False(BwXml.Unpack("assets/engine_config.xml", null));
        }

        [Fact]
        public void Unpack_3()
        {
            Assert.False(BwXml.Unpack("assets/splashscreen.bmp", "assets/engine_config_unpacked_failed.xml"));
        }

        [Fact]
        public void Unpack_4()
        {
            Assert.True(BwXml.Unpack("assets/engine_config.xml", "assets/engine_config_unpacked.xml"));
        }

        [Fact]
        public void Unpack_5()
        {
            Assert.True(BwXml.Unpack("assets/engine_config.xml", "assets/engine_config_unpacked.xml"));

            var xd = XDocument.Load("assets/engine_config_unpacked.xml");
            Assert.NotNull(xd);
            Assert.True(xd.Root.HasElements);
        }

        [Fact]
        public void Unpack_6()
        {
            Assert.True(BwXml.Unpack("assets/engine_config.xml", "assets/engine_config_unpacked.xml"));
            Assert.True(BwXml.Unpack("assets/engine_config_unpacked.xml", "assets/engine_config_unpacked2.xml"));

            var xd = XDocument.Load("assets/engine_config_unpacked2.xml");
            Assert.NotNull(xd);
            Assert.True(xd.Root.HasElements);
        }
    }
}
