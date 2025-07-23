//
// Includes
//

#include "api_fs.h"
#include "fs/fs.h"
#include "fs/fs_search.h"

using namespace OpenWG::Utils;



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

uint32_t FS_FileSizeW(const wchar_t* path_1)
{
    if(!FS_FileExistsW(path_1)){
        return 0;
    }
    return Filesystem::Size(path_1);
}


void* FS_Search_QueryFolderW(const wchar_t* path, uint32_t max_depth){
    void *result = nullptr;

    if(path && path[0] != L'\0') {
        auto *fs_search = new FS::Search();
        fs_search->QueryFolder(path, max_depth);
        result = fs_search;
    }

    return result;
}

bool FS_Search_Close(void* object){
    bool result = false;

    if (object) {
        auto *obj = reinterpret_cast<FS::Search *>(object);
        delete obj;
        result = true;
    }

    return result;
}


uint32_t FS_Search_GetCount(void* object) {
    uint32_t result = 0U;

    if (object) {
        auto *obj = reinterpret_cast<FS::Search *>(object);
        result = obj->GetCount();
    }

    return result;
}

uint32_t FS_Search_GetPathW(void* object, uint32_t index, wchar_t* buf, uint32_t buf_len) {
    uint32_t result = 0;
    if(!object) {
        return result;
    }
    if(!buf && buf_len){
        return result;
    }

    auto *obj = reinterpret_cast<FS::Search *>(object);
    auto str = obj->GetItem(index).wstring();
    result = str.size();

    if (buf && buf_len > result) {
        buf[0] = L'\0';
        wcsncpy(buf, str.c_str(), buf_len - 1);
        buf[buf_len - 1] = L'\0';
    }

    return result;
}
