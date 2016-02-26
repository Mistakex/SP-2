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

void Astronaut::UpgradeWeapon(Weapon& weap,Player& p)
{
	if (p.getResources() < weap.getUpgradeCost())
	{
		upgradeSuccess = false;
		enablePurchaseWindow = false;
		return;
	}
	else
	{
		p.ObtainResources(-(weap.getUpgradeCost()));
		weap.setUpgradeCost(weap.getUpgradeCost() * 1.5);
		weap.Damage *= 1.5;
		upgradeSuccess = true;
		enablePurchaseWindow = false;
	}
}

void Astronaut::UpgradeTurret(Player& p)
{
	if (p.getResources() < TurretNewDmg)
	{
		upgradeSuccess = false;
		enablePurchaseWindow = false;
		return;
	}
	else
	{
		p.ObtainResources(-TurretNewDmg);
		TurretNewDmg *= 1.5;
		upgradeSuccess = true;
		enablePurchaseWindow = false;
	}
}

void Astronaut::PurchaseHarvestor(Player& p)
{
	// Limits the number of Harvestors to 3
	if (Harvestor.size() >= 3)
	{
		purchaseSuccess = false;
		enablePurchaseWindow = true;
		return;
	}
	if (p.getResources() < 50)
	{
		upgradeSuccess = false;
		enablePurchaseWindow = false;
		return;
	}
	else
	{
		Harvestors newHarvestor((0, 0, 0), 1);
		Harvestor.push_back(newHarvestor);
		p.ObtainResources(-50);
		purchaseSuccess = true;
		enablePurchaseWindow = true;
	}
}
