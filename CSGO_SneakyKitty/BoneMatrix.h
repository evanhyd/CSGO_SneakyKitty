#pragma once
#include <cstdint>


class Position;

class BoneMatrix
{
	uint8_t pad0[12];
public:

	float x_;

private:
	uint8_t pad1[12];
public:

	float y_;

private:
	uint8_t pad2[12];
public:

	float z_;


	enum DefinitionIndex : int
	{
		//kStomach = 3,
		//kLowerSpine,
		kSpine = 5,
		kChest,
		kNeck,
		kHead
	};

	explicit operator Position() const;

	static constexpr int kMaxBoneNum = 9;
	static constexpr int kUsefulBoneNum = 4;
	static constexpr int kBoneBegin = kSpine;
	static constexpr int kBoneEnd = kHead;
	static constexpr float kPlayerRadius = 32.0f; //32 is half of a player's width
	static constexpr float kBoneRadius[kMaxBoneNum] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 4.0f, 1.0f, 1.8f};
};

