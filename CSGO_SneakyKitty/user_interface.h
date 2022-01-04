#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <sstream>

namespace user_interface
{
    enum ChatColor : char8_t
    {
        kNull,
        kWhite,
        kRed,
        kLightYellow,
        kGreen,
        kLightGreen,
        kMediumGreen,
        kMediumRed,
        kGrey,
        kYellow,
        kLightBlue = 11,
        kBlue,
        kLightGrey,
        kPurple,
        kLightRed,
        kGold
    };

    const std::u8string kNewLine = u8"\x2029";//it seems required two char8_t

    extern std::unordered_map <std::string, char8_t> chat_color_map;
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

    int CHelp(std::stringstream& ss);
    int CStatus(std::stringstream& ss);
    int CConnect(std::stringstream& ss);
    int CBuyAllPistols(std::stringstream& ss);
    int CDropAll(std::stringstream& ss);
    int CUpdateVoice(std::stringstream& ss);
    int CRecordVoice(std::stringstream& ss);
    int CPlayVoice(std::stringstream& ss);
    int CExpose(std::stringstream& ss);
    int CSetAngle(std::stringstream& ss);
    int CRecordPos(std::stringstream& ss);
    int CInGameConfig(std::stringstream& ss);
    int CRadio(std::stringstream& ss);


    int CTest(std::stringstream& ss);


}
