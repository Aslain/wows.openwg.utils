#pragma once

//
// Includes
//

#include <cstdint>



//
// Public
//

namespace OpenWG::Utils::WWISE {

    enum class SectionType: uint32_t {
        BKHD = 0x44484B42U,
        DATA = 0x41544144U,
        DIDX = 0x58444944U,
        EHVS = 0x53564E45U,
        HIRC = 0x43524948U,
        STID = 0x44495453U,
        STMG = 0x474D5453U,
    };
}
