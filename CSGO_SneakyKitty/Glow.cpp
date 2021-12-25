#include "Glow.h"

DWORD Glow::GetAddress() const
{
	return this->entity_address_;
}

void Glow::SetGlow(int style, float new_red, float new_green, float new_blue, float new_alpha, bool render_occluded, bool render_unocculuded)
{
	this->glow_style_ = style;
	this->red_ = new_red;
	this->green_ = new_green;
	
	this->blue_ = new_blue; //0.0f
	this->alpha_ = new_alpha; //1.0f

	this->render_occluded_ = render_occluded; //true
	this->render_unocculuded_ = render_unocculuded; //false
}

void Glow::SetGlow(int style, int health)
{
	float g = static_cast<float>(health) / 100.0f;
	float r = 1.0f - g;

	this->glow_style_ = style;
	this->red_ = r;
	this->green_ = g;

	this->blue_ = 0.0f;
	this->alpha_ = 1.0f;

	this->render_occluded_ = true;
	this->render_unocculuded_ = false;
}