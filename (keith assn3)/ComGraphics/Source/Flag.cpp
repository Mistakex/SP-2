#include"Flag.h"



Flag::Flag() : flagHp(100), isEnemyflag(false)
{

}

Flag::Flag(const Vector3 &coords) : flagHp(100), isEnemyflag(false)
{
	FLAGPOLE = coords;

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

short Flag::FlagRepair()
{
	flagHp++;
	return flagHp;
}

float Flag::FlagHeightIncrease(const float &target, const double &dt)
{
	float speed = 1;
	if (flagheight < target)
	{
		flagheight += speed * dt;
	}

	return flagheight;
}

float Flag::FlagHeightDecrease(const float &target, const double &dt)
{
	float speed = 1;
	if (flagheight > target)
	{
		flagheight -= speed * dt;
	}
	if (flagheight <= 7.5)
	{
		flagheight = target;
	}

	return flagheight;
}