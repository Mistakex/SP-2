#include"Flag.h"



Flag::Flag() : flagHp(100), isEnemyflag(false)
{
	flagheight = 2.5;
}

Flag::Flag(const Vector3 &coords) : flagHp(100), isEnemyflag(false)
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

short Flag::FlagTakeDmg(const short &amount)
{
	flagHp -= amount;
	return flagHp;
}

short Flag::FlagRepair(const short &amount)
{
	flagHp += amount;
	return flagHp;
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