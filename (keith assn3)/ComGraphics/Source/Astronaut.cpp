#include "Astronaut.h"


Astronaut::Astronaut(Vector3 pos)
{
	Position = pos;
}

Astronaut::~Astronaut()
{
}

Vector3 Astronaut::GetAstronautPos()
{
	return Position;
}

void Astronaut::AstronautMoveAround()
{

}

Weapon Astronaut::UpgradeWeapon(Weapon weap,Player p)
{
	if (p.getResources() < weap.getUpgradeCost())
	{
		return weap;
	}

	p.ObtainResources(-(weap.getUpgradeCost()));
	weap.setUpgradeCost(weap.getUpgradeCost() * 1.5);
	weap.Damage *= 1.5;

	return weap;
	
}
