#pragma once

//
// Includes
//

#include <array>
#include <cstdint>
#include <string>


//
// Public
//

namespace OpenWG::Utils::WWISE {
    struct License {
        std::array<uint32_t, 4> m_key;
    };
}
