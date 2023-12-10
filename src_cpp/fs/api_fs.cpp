//
// Includes
//

#include "api_fs.h"
#include "fs.h"


//
// Implementation
//

bool FS_FileEqualW(const wchar_t *path_1, const wchar_t *path_2) {
    if (!path_1 || !path_2) {
        return false;
    }
    return OpenWG::Utils::Filesystem::IsEqual(path_1, path_2);
}


bool FS_FileExistsW(const wchar_t* path) {
    if (!path) {
        return false;
    }

    return OpenWG::Utils::Filesystem::Exists(path);
}

