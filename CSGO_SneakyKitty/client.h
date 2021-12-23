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

    constexpr int kMaxPlayer = 32;


    /*void UpdateClient();*/
}

