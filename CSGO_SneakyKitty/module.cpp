#include "module.h"
#include <TlHelp32.h>

HANDLE module::csgo_proc_handle = nullptr;
HWND module::csgo_console_window = nullptr; //csgo console window
DWORD module::csgo_process_id = NULL;
DWORD module::client_dll = NULL;
DWORD module::engine_dll = NULL;


void module::InitCSGOProcessHandle()
{
    HWND csgo_window_handle = nullptr;

    do
    {
        csgo_window_handle = FindWindow(NULL, "Counter-Strike: Global Offensive - Direct3D 9");
        Sleep(1000);

    } while (csgo_window_handle == nullptr);

    //obtain the process ID
    GetWindowThreadProcessId(csgo_window_handle, &module::csgo_process_id);

    //obtain the process handle
    module::csgo_proc_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, module::csgo_process_id);
}

void module::InitCSGOConsoleWindow()
{
    do
    {
        csgo_console_window = FindWindowA("Valve001", NULL);
    } while (csgo_console_window == nullptr);
}

DWORD module::GetModuleBaseAddress(const std::string& module_name)
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, module::csgo_process_id);

    //create module entry scanner
    MODULEENTRY32 module_entry;
    module_entry.dwSize = sizeof(MODULEENTRY32);

    do
    {
        //found module
        if (module_entry.szModule == module_name)
        {
            CloseHandle(snapshot);
            return reinterpret_cast<DWORD>(module_entry.modBaseAddr);
        }
    } while (Module32Next(snapshot, &module_entry));

    CloseHandle(snapshot);
    return NULL;
}

