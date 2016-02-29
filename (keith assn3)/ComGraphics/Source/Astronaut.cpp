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
	// Sets cost of one harvestor to be 50 resources
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

void Astronaut::PurchaseGrenades(Player& p)
{
	// Limits number of grenades held to 5
	if (p.noOfGrenadesHeld >= 5)
	{
		purchaseSuccess = false;
		enablePurchaseWindow = true;
		return;
	}
	// Sets cost of 1 grenade to be at 30
	if (p.getResources() < 30)
	{
		upgradeSuccess = false;
		enablePurchaseWindow = false;
		return;
	}
	else
	{
		p.noOfGrenadesHeld++;
		p.ObtainResources(-30);
		purchaseSuccess = true;
		enablePurchaseWindow = true;
	}
}
void Astronaut::UpgradeGrenadeDamage(Player& p)
{
	// Sets cost of upgrade to be at 30 + 25*(number of times upgraded)
	if (p.getResources() < (GrenadeDamage - 100) + 30)
	{
		upgradeSuccess = false;
		enablePurchaseWindow = false;
		return;
	}
	else
	{
		GrenadeDamage += 25;
		p.ObtainResources(-((GrenadeDamage - 100) + 30));
		upgradeSuccess = true;
		enablePurchaseWindow = false;
	}
}
void Astronaut::UpgradeGrenadeRange(Player& p)
{
	if (p.getResources() < (GrenadeRange - 19) * 10)
	{
		upgradeSuccess = false;
		enablePurchaseWindow = false;
		return;
	}
	else
	{
		GrenadeRange += 1;
		p.ObtainResources(-((GrenadeRange - 19) * 10));
		upgradeSuccess = true;
		enablePurchaseWindow = false;
	}
}
void Astronaut::UpgradeMedkitTicks(Player& p, Medkit& m)
{
	if (p.getResources() < (m.MaxTimesHealed) * 10)
	{
		upgradeSuccess = false;
		enablePurchaseWindow = false;
		return;
	}
	else
	{
		m.MaxTimesHealed += 1;
		p.ObtainResources(-(m.MaxTimesHealed) * 10);
		upgradeSuccess = true;
		enablePurchaseWindow = false;
	}
}
void Astronaut::UpgradeMedkitHeal(Player& p, Medkit& m)
{
	if (p.getResources() < (m.HealAmount/10)*35)
	{
		upgradeSuccess = false;
		enablePurchaseWindow = false;
		return;
	}
	else
	{
		m.HealAmount += 10;
		p.ObtainResources(-(m.HealAmount / 10) * 35);
		upgradeSuccess = true;
		enablePurchaseWindow = false;
	}
}
