#pragma once
#include "offsets.h"
#include "Vector3.h"

class Entity
{

public:

	enum Flag : int
	{
		FL_ONGROUND = 1 << 0, // On the floor
	    FL_DUCKING = 1 << 1, // Crouching
	    FL_WATERJUMP = 1 << 3,
	    FL_ONTRAIN = 1 << 4,
	    FL_INRAIN = 1 << 5,
	    FL_FROZEN = 1 << 6,// Frozen
	    FL_ATCONTROLS = 1 << 7,
	    FL_CLIENT = 1 << 8,
	    FL_FAKECLIENT = 1 << 9,
	    FL_INWATER = 1 << 10,// In water
	    FL_HIDEHUD_SCOPE = 1 << 11,
	};


	enum Team : int
	{
		kInvalid = -1,
		kUnknown,
		kSpectator,
		kT,
		kCT,
		kAll //artificial
	};


	//padding
private:
	char pad0_;
public:

	bool dormant_;//237

private:
	char pad1_[offsets::m_iTeamNum - offsets::m_bDormant - sizeof(dormant_)];
public:

	int team_; //244

private:
	char pad2_[offsets::m_iHealth - offsets::m_iTeamNum - sizeof(team_)];
public:

	int health_; //256
	int flag_;
	Vector3 view_offset_;
	Vector3 velocity_;//275

private:
	char pad3_[offsets::m_vecOrigin - offsets::m_vecVelocity - sizeof(velocity_)];
public:

	Vector3 origin_;//312

private:
	char pad4_[offsets::m_bSpotted - offsets::m_vecOrigin - sizeof(origin_)];
public:

	bool spotted_;

private:
	char pad5_[offsets::m_bSpottedByMask - offsets::m_bSpotted - sizeof(spotted_)];
public:

	int spotted_by_mask_;


	Entity() = default;

	bool IsAlly(const Entity& entity);
};

