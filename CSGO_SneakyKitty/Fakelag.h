#pragma once
class Fakelag
{
public:
    void operator()(int update_period_ms);
    void ChokePackets(int max_choke_ticks);
};

