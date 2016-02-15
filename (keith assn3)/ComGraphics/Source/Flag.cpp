#include"Flag.h"



Flag::Flag() : flagHp(100), ifEnemyflag(false)
{

}

Flag::Flag(const Vector3 coords) : flagHp(100), ifEnemyflag(false)
{
	FLAG = coords;
}
Flag::~Flag()
{
}

short Flag::FlagTakeDmg(short amount)
{
	flagHp -= amount;
	return flagHp;
}

short Flag::FlagRepair()
{
	flagHp++;
	return flagHp;
}

float Flag::FlagHeightCoord(float target)
{
	while (flagheight < target)
	{
		flagheight++;
	}
	return flagheight;
}