#pragma once
#include <Windows.h>


class PlayerEntityAddress
{
public:
	DWORD entity_address;

private:
	char pad0_[12];

//public:
//	static PlayerEntityAddress player_entity_address_list[client::MAX_PLAYER];
};

