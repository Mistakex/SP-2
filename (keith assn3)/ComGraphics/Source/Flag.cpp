#include"Flag.h"



Flag::Flag() : flagHp(100), isEnemyflag(false)
{

}

Flag::Flag(const Vector3 &coords) : flagHp(100), isEnemyflag(false)
{
	FLAG = coords;
}
Flag::~Flag()
{
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

float Flag::FlagHeightCoord(const float &target,const double &dt)
{
	float speed = 1;
	while (flagheight < target)
	{
		flagheight += speed * dt;
	}
	if (flagheight > target)
	{
		flagheight = target;
	}
	return flagheight;
}