#pragma once

using byte = unsigned char;

class Cham
{
public:
	byte red_;
	byte green_;
	byte blue_;
	byte alpha_;

	Cham() = default;
	constexpr Cham(byte new_red, byte new_green, byte new_blue, byte new_alpha) : red_(new_red), green_(new_green), blue_(new_blue), alpha_(new_alpha)
	{
		//empty
	}
};
