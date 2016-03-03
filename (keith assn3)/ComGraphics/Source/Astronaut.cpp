/******************************************************************************/
/*!
\file	Astronaut.cpp
\author Lim Zhi Yuan
\par	email: 153432X\@mymail.nyp.edu.sg
\brief
Class for the Astronaut, which functions as the shop for players to upgrade, and
purchase items.
*/
/******************************************************************************/
#include "Astronaut.h"

/******************************************************************************/
/*!
\brief
Constructor for Astronaut class

\param	pos
Position that the Astronaut will spawn at.
*/
/******************************************************************************/
Astronaut::Astronaut(Vector3 pos)
{
	Position = pos;
}

/******************************************************************************/
/*!
\brief
Default destructor for Astronaut class
*/
/******************************************************************************/

Astronaut::~Astronaut()
{
}

/******************************************************************************/
/*!
\brief
A getter function for Astronaut's position
\return
Returns the position of the Astronaut
*/
/******************************************************************************/

Vector3 Astronaut::GetAstronautPos()
{
	return Position;
}

/******************************************************************************/
/*!
\brief
Function to upgrade a weapon that the player has.
\param weap
Weapon to be upgraded
\param p
Player - To reduce the resources needed from.
*/
/******************************************************************************/

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
		weap.setUpgradeCost((int)(weap.getUpgradeCost() * 1.5));
		weap.Damage = (int)(weap.Damage * 1.5);
		upgradeSuccess = true;
		enablePurchaseWindow = false;
	}
}

/******************************************************************************/
/*!
\brief
Function to upgrade the turret's damage
\param p
Player - To reduce the resources needed from.
*/
/******************************************************************************/
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
		TurretNewDmg = (int)(TurretNewDmg *1.5);
		upgradeSuccess = true;
		enablePurchaseWindow = false;
	}
}

/******************************************************************************/
/*!
\brief
Function to purchase a Harvestor from the Astronaut
\param p
Player - To reduce the resources needed from.
*/
/******************************************************************************/
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
		Harvestors newHarvestor(Vector3(0, 0, 0), 0.5f);
		Harvestor.push_back(newHarvestor);
		p.ObtainResources(-50);
		purchaseSuccess = true;
		enablePurchaseWindow = true;
	}
}

/******************************************************************************/
/*!
\brief
Function to purchase Grenades from the Astronaut.
\param p
Player - To reduce the resources needed from.
*/
/******************************************************************************/

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

/******************************************************************************/
/*!
\brief
Function to upgrade the grenade's damage.
\param p
Player - To reduce the resources needed from.
*/
/******************************************************************************/

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
		p.ObtainResources(-((GrenadeDamage - 100) + 30));
		GrenadeDamage += 25;
		upgradeSuccess = true;
		enablePurchaseWindow = false;
	}
}

/******************************************************************************/
/*!
\brief
Function to upgrade the grenade's flying range.
\param p
Player - To reduce the resources needed from.
*/
/******************************************************************************/

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
		p.ObtainResources(-((GrenadeRange - 19) * 10));
		GrenadeRange += 1;
		upgradeSuccess = true;
		enablePurchaseWindow = false;
	}
}

/******************************************************************************/
/*!
\brief
Function to upgrade the number of times the Medkit heals per use.
\param p
Player - To reduce the resources needed from.
\param m
Medkit to be upgraded.
*/
/******************************************************************************/

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
		p.ObtainResources(-(m.MaxTimesHealed) * 10);
		m.MaxTimesHealed += 1;
		upgradeSuccess = true;
		enablePurchaseWindow = false;
	}
}

/******************************************************************************/
/*!
\brief
Function to upgrade how much health the Medkit recovers per tick. 
\param p
Player - To reduce the resources needed from.
\param m
Medkit to be upgraded.
*/
/******************************************************************************/

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
		p.ObtainResources(-(m.HealAmount / 10) * 35);
		m.HealAmount += 10;
		upgradeSuccess = true;
		enablePurchaseWindow = false;
	}
}

/******************************************************************************/
/*!
\brief
Function to reset the medkit's upgrade cost, ticks, and amount of health
recovered per use.
\param m
Medkit to reset.
*/
/******************************************************************************/
void Astronaut::resetMedkitUpgrades(Medkit& m)
{
	m.HealAmount = m.initialHealingAmount;
	m.MaxTimesHealed = m.initialTicks;
}

/******************************************************************************/
/*!
\brief
Function to reset a weapon's damage and upgrade cost.
\param weap
Weapon to reset.
*/
/******************************************************************************/
void Astronaut::resetWeaponUpgrades(Weapon& weap)
{
	weap.Damage = weap.initialDamage;
	weap.setUpgradeCost(weap.initialUC);
}

/******************************************************************************/
/*!
\brief
Function to reset the upgrade cost of Turrets, Grenades, and amount of Harvestors.
*/
/******************************************************************************/
void Astronaut::resetAllUpgrades()
{
	TurretNewDmg = 20;
	GrenadeDamage = 100;
	GrenadeRange = 20;

	while (!Harvestor.empty())
	{
		Harvestor.pop_back();
	}
}