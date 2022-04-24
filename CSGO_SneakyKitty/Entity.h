#pragma once
#include "offsets.h"
#include "Vector3.h"
#include "Position.h"

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

private:
	//padding
	char pad0_;
	bool dormant_;//237
	char pad1_[0xF4 - 0xED - sizeof(dormant_)]; //m_iTeamNum - m_bDormant - sizeof(dormant_)
	int team_; //244
	char pad2_[0x100 - 0xF4 - sizeof(team_)]; //m_iHealth - m_iTeamNum - sizeof(team_)
	int health_; //256
	int flag_;
	Position view_offset_;
	Vector3 velocity_; //275
	char pad3_[0x138 - 0x114 - sizeof(velocity_)]; //m_vecOrigin - m_vecVelocity - sizeof(velocity_)
	Position origin_; //312
	char pad4_[0x93D - 0x138 - sizeof(origin_)]; //m_bSpotted - m_vecOrigin - sizeof(origin_)
	bool spotted_;
	char pad5_[0x980 - 0x93D - sizeof(spotted_)]; //m_bSpottedByMask - m_bSpotted - sizeof(spotted_)
	int spotted_by_mask_;


public:



	Entity() = default;

	bool IsOnGround() const;
	bool IsDucking() const;
	bool IsWaterJump() const;
	bool IsOnTrain() const;
	bool IsInRain() const;
	bool IsFrozen() const;
	bool IsAtControls() const;
	bool IsClient() const;
	bool IsFakeClient() const;
	bool IsInWater() const;
	bool IsHideHudScope() const;

	bool IsDormant() const;
	int GetHealth() const;
	int GetTeam() const;
	int GetSpottedMask() const;
	const Position& GetOrigin() const;
	float GetViewOffsetZ() const;

	bool IsAlive() const;
	bool IsDead() const;
	bool IsEnemy(const Entity& entity) const;
	bool IsAlly(const Entity& entity) const;
};

