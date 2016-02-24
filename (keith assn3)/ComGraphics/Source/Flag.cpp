#include"Flag.h"



Flag::Flag() : isEnemyflag(false)
{
	flagheight = 2.5;
}

Flag::Flag(const Vector3 &pos, const Vector3 &rangexyz) : isEnemyflag(false)
{
	position = pos;
	this->rangexyz = rangexyz;
	flagheight = 2.5;
}
Flag::~Flag()
{
}

float Flag::getMagnitude(const Vector3 &target)
{
	Vector3 view = target - position;
	return sqrt(pow(view.x, 2) + pow(view.y, 2) + pow(view.z, 2));
}

float Flag::FlagHeightIncrease(const float &target, const double &dt)
{
	float speed = 0.1;
	if (flagheight < target)
	{
		flagheight += speed * dt;
	}

	return flagheight;
}

float Flag::FlagHeightDecrease(const float &target, const double &dt)
{
	float speed = 0.1;
	if (flagheight > target)
	{
		flagheight -= speed * dt;
	}
	if (flagheight <= target)
	{
		flagheight = target;
	}
	return flagheight;
}