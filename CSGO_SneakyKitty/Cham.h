#pragma once
#include <cstdint>

class Cham
{
public:
	uint8_t red_;
	uint8_t green_;
	uint8_t blue_;
	uint8_t alpha_;

	Cham() = default;
	constexpr Cham(uint8_t new_red, uint8_t new_green, uint8_t new_blue, uint8_t new_alpha) : red_(new_red), green_(new_green), blue_(new_blue), alpha_(new_alpha)
	{
		//empty
	}
};
