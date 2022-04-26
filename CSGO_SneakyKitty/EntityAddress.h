#pragma once
#include <Windows.h>
#include <cstdint>

class EntityAddress
{
	DWORD address_;
	uint8_t pad0_[12];

public:
	DWORD GetAddress() const;
};

