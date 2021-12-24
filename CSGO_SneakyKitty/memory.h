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
    void ReadMem(HANDLE process_handle, DWORD address, T& dest, SIZE_T byte_size)
    {
        ReadProcessMemory(process_handle, reinterpret_cast<LPCVOID>(address), &dest, byte_size, NULL);
    }

    template <class T>
    void WriteMem(HANDLE process_handle, DWORD address, const T& srce)
    {
        WriteProcessMemory(process_handle, reinterpret_cast<LPVOID>(address), &srce, sizeof(srce), NULL);
    }

    template <class T>
    void WriteMem(HANDLE process_handle, DWORD address, const T& srce, SIZE_T byte_size)
    {
        WriteProcessMemory(process_handle, reinterpret_cast<LPVOID>(address), &srce, byte_size, NULL);
    }
}
