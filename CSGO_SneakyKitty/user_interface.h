#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <sstream>

namespace user_interface
{
    void InitUserInterface();
    void GUI();


    void SendConsoleCommand(const std::string& command_line);
    void SendBuiltInCommand(const std::string& command_line);

    int CHelp(std::stringstream& ss);
    int CConnect(std::stringstream& ss);
    int CBuyAllPistols(std::stringstream& ss);
    int CDropAll(std::stringstream& ss);
    int CUpdateVoice(std::stringstream& ss);
    int CRecordVoice(std::stringstream& ss);
    int CPlayVoice(std::stringstream& ss);
    int CExpose(std::stringstream& ss);
    int CSetAngle(std::stringstream& ss);


    extern std::unordered_map <std::string, std::function<int(std::stringstream&)>> command_map;
}
