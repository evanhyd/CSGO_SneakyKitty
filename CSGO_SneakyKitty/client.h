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

    constexpr int kMaxPlayerNum = 32;
    constexpr float kMaxLagCompensation = 200.0f; //200 ms
}

