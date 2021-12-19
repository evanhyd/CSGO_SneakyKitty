#pragma once

namespace client
{
    enum ConnectionState : int
    {
        kNone,
        kChallenge,
        kConnected, //loading screen
        kNew,
        kPrespawn,
        kSpawn,
        kFullyConnected, //fully connected to the game
        kChangeLevel
    };

    /*
	extern DWORD client_state;
	extern DWORD net_channel;
    */

    extern int connection_status;

    constexpr int kMaxPlayer = 32;

    void UpdateClient();
}

