#include "osversion.h"

// ---------------------------------------------
// Source: https://stackoverflow.com/a/27323983
// ---------------------------------------------

#include <windows.h>
#include <stdint.h>
#include <memory>

bool GetOSVersionStringW(WCHAR* version, size_t maxlen)
{
    WCHAR path[_MAX_PATH];
    if (!GetSystemDirectoryW(path, _MAX_PATH))
        return false;

    wcscat_s(path, L"\\kernel32.dll");

    //
    // Based on example code from this article
    // http://support.microsoft.com/kb/167597
    //

    DWORD handle;
#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
    DWORD len = GetFileVersionInfoSizeExW(FILE_VER_GET_NEUTRAL, path, &handle);
#else
    DWORD len = GetFileVersionInfoSizeW(path, &handle);
#endif
    if (!len)
        return false;

    std::unique_ptr<uint8_t> buff(new (std::nothrow) uint8_t[len]);
    if (!buff)
        return false;

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
    if (!GetFileVersionInfoExW(FILE_VER_GET_NEUTRAL, path, 0, len, buff.get()))
#else
    if (!GetFileVersionInfoW(path, 0, len, buff.get()))
#endif
        return false;

    VS_FIXEDFILEINFO* vInfo = nullptr;
    UINT infoSize;

    if (!VerQueryValueW(buff.get(), L"\\", reinterpret_cast<LPVOID*>(&vInfo), &infoSize))
        return false;

    if (!infoSize)
        return false;

    swprintf_s(version, maxlen, L"%u.%u.%u.%u",
        HIWORD(vInfo->dwFileVersionMS),
        LOWORD(vInfo->dwFileVersionMS),
        HIWORD(vInfo->dwFileVersionLS),
        LOWORD(vInfo->dwFileVersionLS));

    return true;
}

bool GetOSVersionStringA(char* version, size_t maxlen)
{
    // For some reason GetFileVersionInfoSizeExA and GetFileVersionInfoExA are missing from version.lib in the windows sdk.
    // The correct implementation is beneath but this will have to do for now.
    WCHAR* v = reinterpret_cast<WCHAR*>(malloc((maxlen + 1) * 2));
    if (!GetOSVersionStringW(v, maxlen))
        return false;
    if (v == nullptr)
        return false;
    wcstombs(version, v, maxlen);
    return true;

    /*char path[_MAX_PATH];
    if (!GetSystemDirectoryA(path, _MAX_PATH))
        return false;

    strcat_s(path, "\\kernel32.dll");

    //
    // Based on example code from this article
    // http://support.microsoft.com/kb/167597
    //

    DWORD handle;
#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
    DWORD len = GetFileVersionInfoSizeExA(FILE_VER_GET_NEUTRAL, path, &handle);
#else
    DWORD len = GetFileVersionInfoSizeA(path, &handle);
#endif
    if (!len)
        return false;

    std::unique_ptr<uint8_t> buff(new (std::nothrow) uint8_t[len]);
    if (!buff)
        return false;

#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
    if (!GetFileVersionInfoExA(FILE_VER_GET_NEUTRAL, path, 0, len, buff.get()))
#else
    if (!GetFileVersionInfoA(path, 0, len, buff.get()))
#endif
        return false;

    VS_FIXEDFILEINFO* vInfo = nullptr;
    UINT infoSize;

    if (!VerQueryValueA(buff.get(), "\\", reinterpret_cast<LPVOID*>(&vInfo), &infoSize))
        return false;

    if (!infoSize)
        return false;

    sprintf_s(version, maxlen, "%u.%u.%u.%u",
        HIWORD(vInfo->dwFileVersionMS),
        LOWORD(vInfo->dwFileVersionMS),
        HIWORD(vInfo->dwFileVersionLS),
        LOWORD(vInfo->dwFileVersionLS));

    return true;*/
}

