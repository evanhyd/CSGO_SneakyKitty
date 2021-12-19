#pragma once
class GlobalVar
{
public:
	float realtime_;
	int frame_count_;
	float absolute_frametime_;
	float unknown_;
	float curtime_;
	float frametime_;
	int max_clients_;
	int tick_count_; 
	float interval_per_tick_;
	float interpolation_amount_;
};

