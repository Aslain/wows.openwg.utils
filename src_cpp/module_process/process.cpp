/* Copyright (c) 2017-2019, Mikhail Paulyshka
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "process.h"

#include <Windows.h>
#include <TlHelp32.h>
#include <Psapi.h>


const wchar_t* wcsistr(const wchar_t *wcs1, const wchar_t *wcs2)
{
    const wchar_t *s1, *s2;
    const wchar_t l = towlower(*wcs2);
    const wchar_t u = towupper(*wcs2);

    if (!*wcs2)
        return wcs1; // an empty substring matches everything

    for (; *wcs1; ++wcs1)
    {
        if (*wcs1 == l || *wcs1 == u)
        {
            s1 = wcs1 + 1;
            s2 = wcs2 + 1;

            while (*s1 && *s2 && towlower(*s1) == towlower(*s2))
                ++s1, ++s2;

            if (!*s2)
                return wcs1;
        }
    }

    return nullptr;
}

static HRESULT NormalizeNTPath(wchar_t* pszPath, size_t nMax)
{
    #define NUMCHARS(a) (sizeof(a)/sizeof(*a))

    wchar_t* pszSlash = wcschr(&pszPath[1], '\\');
    if (pszSlash) pszSlash = wcschr(pszSlash + 1, '\\');
    if (!pszSlash)
        return E_FAIL;

    wchar_t cSave = *pszSlash;
    *pszSlash = 0;

    wchar_t szNTPath[MAX_PATH];
    wchar_t szDrive[MAX_PATH] = L"A:";

    for (wchar_t cDrive = L'A'; cDrive < L'Z'; ++cDrive)
    {
        szDrive[0] = cDrive;
        szNTPath[0] = 0;
        if (0 != QueryDosDeviceW(szDrive, szNTPath, NUMCHARS(szNTPath)) && 0 == _wcsicmp(szNTPath, pszPath))
        {
            // Match
            wcscat_s(szDrive, NUMCHARS(szDrive), L"\\");
            wcscat_s(szDrive, NUMCHARS(szDrive), pszSlash + 1);
            wcscpy_s(pszPath, nMax, szDrive);
            return S_OK;
        }
    }
    *pszSlash = cSave;
    return E_FAIL;
}


std::vector<std::wstring> Process::GetRunningProcessesInDirectory(wchar_t* directoryName)
{
    std::vector<std::wstring> procs;
    wchar_t pName[512];

    if (directoryName == nullptr)
        return procs;

    HANDLE hProcessSnap  = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnap == INVALID_HANDLE_VALUE)
        return procs;

    PROCESSENTRY32W pe32{ 0 };
    pe32.dwSize = sizeof(pe32);

    if (!Process32FirstW(hProcessSnap, &pe32))
    {
        MessageBoxA(NULL, std::to_string(GetLastError()).c_str(), "", MB_OK);
        CloseHandle(hProcessSnap);
        return procs;
    }

    do
    {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pe32.th32ProcessID);
        if (hProcess == nullptr)
            continue;

        if (GetProcessImageFileNameW(hProcess, pName, 512) != 0)
        {
            NormalizeNTPath(pName, 512);
            if (wcsistr(pName, directoryName) != nullptr)
                procs.push_back(pe32.szExeFile);
        }

        CloseHandle(hProcess);
    } while (Process32NextW(hProcessSnap, &pe32));


    CloseHandle(hProcessSnap);
    return procs;
}


BOOL CALLBACK TerminateProcessCallback(
    _In_ HWND   hwnd,
    _In_ LPARAM lParam
)
{
    DWORD dwID = 0;
    PDWORD_PTR lResult = nullptr;

    GetWindowThreadProcessId(hwnd, &dwID);

    if (dwID == lParam)
    {
        return SendMessageTimeoutW(hwnd, WM_CLOSE, 0, 0, SMTO_BLOCK | SMTO_ABORTIFHUNG, 5000, lResult) != 0;
    }
    else
    {
        return true;
    }
}

bool Process::TerminateProcess(wchar_t* processName)
{
    if (processName == nullptr)
        return false;

    if (processName[0] == L'\0')
        return false;


    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);


    if (hProcessSnap == INVALID_HANDLE_VALUE)
        return false;

    PROCESSENTRY32W pe32{ 0 };
    pe32.dwSize = sizeof(pe32);

    if (!Process32FirstW(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return false;
    }

    bool flag = false;
    do
    {
        if (wcsistr(pe32.szExeFile, processName) == nullptr)
            continue;

        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE | PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | SYNCHRONIZE, FALSE, pe32.th32ProcessID);

        if (hProcess == nullptr)
            continue;

        //soft exit
        if (EnumWindows(TerminateProcessCallback, pe32.th32ProcessID))
        {
            switch (WaitForSingleObject(hProcess, 5000))
            {
                case WAIT_OBJECT_0:
                    CloseHandle(hProcess);
                    CloseHandle(hProcessSnap);
                    return true;
                default:
                    break;
            }
        }

        ::TerminateProcess(hProcess, 9);

        CloseHandle(hProcess);
        flag = true;

    } while (Process32NextW(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);

    return flag;
}
