//
// Includes
//

#include "api_fs.h"
#include "fs.h"


//
// Implementation
//

bool FS_File_IsEqualW(const wchar_t *path_1, const wchar_t *path_2) {
    if (!path_1 || !path_2) {
        return false;
    }
    return OpenWG::Utils::Filesystem::IsEqual(path_1, path_2);
}
