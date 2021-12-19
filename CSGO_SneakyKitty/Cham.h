#pragma once

class Cham
{
public:
	char red_;
	char green_;
	char blue_;
	char alpha_;

	Cham() = default;
	constexpr Cham(char new_red, char new_green, char new_blue, char new_alpha) : red_(new_red), green_(new_green), blue_(new_blue), alpha_(new_alpha)
	{
		//empty
	}
};
