#include <iostream>
#include <string>
#include <sstream>

#include <io.h>
#include <fcntl.h>

#include "common/string.h"
#include "module_process/api_process.h"

std::vector<std::wstring> Split(const std::wstring &s, wchar_t delim) {
    std::vector<std::wstring> elems;
    std::wstringstream ss(s);
    std::wstring item;

    while (std::getline(ss, item, delim)) {
        *(std::back_inserter(elems)++) = item;
    }

    return elems;
}
int main(){
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stderr), _O_U16TEXT);

    wchar_t buf[1024]{};

    auto run_count = PROCESS_GetRunningInDirectoryW(L"F:\\Games\\Wargaming.net\\World_of_Tanks_EU\\",buf,std::size(buf));
    std::wcout << L"run_count: " << run_count <<std::endl;

    auto procs = Split(buf,L';');
    for(const auto& proc: procs){
        std::wcout << "* " << proc << std::endl;
    }

    for (const auto& proc : procs) {
        std::wcout << "terminate" << proc << " -->" << PROCESS_TerminateProcess(proc.c_str()) << std::endl;
    }


    return 0;
}