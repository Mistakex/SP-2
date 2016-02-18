#include"Flag.h"



Flag::Flag() : isEnemyflag(false)
{
	flagheight = 2.5;
}

Flag::Flag(const Vector3 &coords) : isEnemyflag(false)
{
	FLAGPOLE = coords;
	flagheight = 2.5;
}
Flag::~Flag()
{
}

float Flag::getMagnitude(const Vector3 &target)
{
	Vector3 view = target - FLAGPOLE;
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