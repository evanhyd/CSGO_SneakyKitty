#pragma once

class Angle;

class Ragebot
{
public:
    void operator()(int update_period_ms);

private:

    class Packet
    {
    public:
        void operator()(int update_period_ms, int &best_target_id, const Angle& ragebot);
    };
};

