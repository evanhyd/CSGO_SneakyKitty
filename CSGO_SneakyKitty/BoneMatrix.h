#pragma once

class Position;

class BoneMatrix
{
	char pad0[12];
public:

	float x_;

private:
	char pad1[12];
public:

	float y_;

private:
	char pad2[12];
public:

	float z_;


	enum DefinitionIndex : int
	{
		kSpine = 5,
		kChest,
		kNeck,
		kHead
	};

	explicit operator Position() const;

	/*
	static constexpr int MAX_BONE = 4;
	static constexpr float BONE_RADIUS[4] = { 5.0f, 4.0f, 1.0f, 1.8f };
	static Bone bone_list[client::MAX_PLAYER][Bone::MAX_BONE];

	static void UpdateEntityBones();
	*/
};

