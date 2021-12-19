#pragma once
#include <Windows.h>
#include <string>

namespace module
{
    extern HANDLE csgo_process_handle; //csgo process handle
    extern DWORD csgo_process_id; //csgo process id
    extern DWORD client_dll; //client.dll base address
    extern DWORD engine_dll; //engine.dll base address

    void InitCSGOProcessHandle();
    DWORD GetModuleBaseAddress(const std::string& module_name);
}

template <class T>
void rM(DWORD address, T& destination)
{
    ReadProcessMemory(module::csgo_process_handle, reinterpret_cast<LPCVOID>(address), &destination, sizeof(destination), NULL);
}


template <class T>
void wM(DWORD address, const T& source)
{
    WriteProcessMemory(module::csgo_process_handle, reinterpret_cast<LPVOID>(address), &source, sizeof(source), NULL);
}