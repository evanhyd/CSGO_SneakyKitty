#pragma once
#include <Windows.h>

namespace memory
{

    template <class T>
    void ReadMem(HANDLE process_handle, DWORD address, T& dest)
    {
        ReadProcessMemory(process_handle, reinterpret_cast<LPCVOID>(address), &dest, sizeof(dest), NULL);
    }

    template <class T>
    void ReadMem(HANDLE process_handle, DWORD address, T& dest, SIZE_T bytes)
    {
        ReadProcessMemory(process_handle, reinterpret_cast<LPCVOID>(address), &dest, bytes, NULL);
    }

    template <class T>
    void WriteMem(HANDLE process_handle, DWORD address, const T& srce)
    {
        WriteProcessMemory(process_handle, reinterpret_cast<LPVOID>(address), &srce, sizeof(srce), NULL);
    }

    template <class T>
    void WriteMem(HANDLE process_handle, DWORD address, const T& srce, SIZE_T bytes)
    {
        WriteProcessMemory(process_handle, reinterpret_cast<LPVOID>(address), &srce, bytes, NULL);
    }
}
