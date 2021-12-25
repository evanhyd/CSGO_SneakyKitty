#pragma once
#include <Windows.h>
#include "Angle.h"

class Commands0X4
{
public:
	int cmd_number_;
	int tick_count_;

	Angle view_angles_;
	Angle aim_angles_;

	float forward_move_;
	float side_move_;
	float up_move_;
	int buttons_mask_;
};

class Commands
{
	DWORD pad0_; //mysterious hash???

public:
	Commands0X4 cmd_0x4_;

private:
	char pad1_[46];
};

class VerifiedCommands
{
	Commands commands_;
	DWORD pad0_;
};


class Input
{
public:

	enum Button : int
	{
		IN_ATTACK = 1 << 0, // Fire weapon
	    IN_JUMP = 1 << 1, // Jump
	    IN_DUCK = 1 << 2, // Crouch
	    IN_FORWARD = 1 << 3, // Walk forward
	    IN_BACK = 1 << 4, // Walk backwards
	    IN_USE = 1 << 5, // Use (Defuse bomb, etc...)
	    IN_CANCEL = 1 << 6, // ??
	    IN_LEFT = 1 << 7,// Walk left
	    IN_RIGHT = 1 << 8,// Walk right
	    IN_MOVELEFT = 1 << 9,// Alias? (not sure)
	    IN_MOVERIGHT = 1 << 10,// Alias? (not sure)
	    IN_ATTACK2 = 1 << 11,// Secondary fire (Revolver, Glock change fire mode, Famas change fire mode) (not sure)
	    IN_RUN = 1 << 12,
	    IN_RELOAD = 1 << 13,// Reload weapon
	    IN_ALT1 = 1 << 14,
	    IN_ALT2 = 1 << 15,
	    IN_SCORE = 1 << 16,
	    IN_SPEED = 1 << 17,
	    IN_WALK = 1 << 18,// Shift
	    IN_ZOOM = 1 << 19,// Zoom weapon (not sure)
	    IN_WEAPON1 = 1 << 20,
	    IN_WEAPON2 = 1 << 21,
	    IN_BULLRUSH = 1 << 22
	};

	static constexpr int MULTIPLAYER_BACKUP = 150;


private:
	char pad0_[0xc0];

public:
	bool camera_intercepts_with_mouse_;
	bool camera_in_thirdperson_;
	bool camera_rotates_with_mouse_;
	bool pad1_;
	Angle camera_angle_;
	char camera_distance_offset_;

private:
	char pad2_[19];
public:

	bool orthographic;

private:
	char pad3_[3];
public:

	Angle current_view_angles;
	Angle offset_view_angles;
	float last_forward_move;

private:
	int pad4_;
public:

	DWORD pCommands;
	DWORD pVerifiedCommands;
};

