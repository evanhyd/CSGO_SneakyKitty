#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <sstream>

namespace user_interface
{
    extern std::unordered_map <std::string, std::function<int(std::stringstream&)>> command_map;
    void InitUserInterface();


    void SendConsoleCommand(const std::string& command_line);
    void SendConsoleCommand(const std::u8string& command_line);


    void SendBuiltInCommand(const std::string& command_line);
    int HFakeLag(std::stringstream& ss);
    int HRemoveFlash(std::stringstream& ss);
    int HBhop(std::stringstream& ss);
    int HGlowESP(std::stringstream& ss);
    int HRadarESP(std::stringstream& ss);
    int HThirdperson(std::stringstream& ss);
    int HDesync(std::stringstream& ss);
    int HAimbot(std::stringstream& ss);
    int HBacktrack(std::stringstream& ss);
    int HGlobalTarget(std::stringstream& ss);
    int HBombTimer(std::stringstream& ss);

    int CHelp(std::stringstream& ss);
    int CStatus(std::stringstream& ss);
    int CConnect(std::stringstream& ss);
    int CBuyAllPistols(std::stringstream& ss);
    int CDrop(std::stringstream& ss);
    int CUpdateVoice(std::stringstream& ss);
    int CRecordVoice(std::stringstream& ss);
    int CPlayVoice(std::stringstream& ss);
    int CExpose(std::stringstream& ss);
    int CSetAngle(std::stringstream& ss);
    int CRecordPos(std::stringstream& ss);
    int CGameConfig(std::stringstream& ss);
    int CQuit(std::stringstream& ss);

    int CTest(std::stringstream& ss);
}
