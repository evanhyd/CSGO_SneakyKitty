#pragma once
#include <Windows.h>


class EntityAddress
{
	DWORD address_;
	char pad0_[12];

public:
	DWORD GetAddress() const;
};

