#pragma once
#include <string>

namespace user_interface
{
    void SendConsoleCommand(const std::string& command);
    void SendBuiltInCommand(const std::string& command);
    void AdjustConfig(const std::string& command);
    void GUI();
}
