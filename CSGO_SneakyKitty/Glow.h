#pragma once
#include <Windows.h>

class Glow
{
	int next_free_slot_;
	DWORD entity_address_;
	float red_;
	float green_;
	float blue_;
	float alpha_;

	int pad0_[2];

	float bloom_amount_;

	int u1_;

	bool render_occluded_;
	bool render_unocculuded_;

	bool full_bloom_render_;
	char pad1_;

	int full_bloom_stencil_test_value_;
	int glow_style_; //0 full-body  1 inline && flicker  2 inline glow  3 flicker
	int split_screen_shot_;


public:

	enum GlowStyle : int
	{
		kFullBody,
		kInlineFlicker,
		kInline,
		kFlicker
	};


	DWORD GetEntityAddress() const;
	void SetGlow(int style, float new_red, float new_green, float new_blue, float new_alpha, bool render_occluded, bool render_unocculuded);
	void SetGlow(int style, int health);
};

