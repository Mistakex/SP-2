#ifndef ASTRONAUT_H
#define ASTRONAUT_H

#include "Vector3.h"
class Astronaut
{
public:
	Astronaut();
	~Astronaut();
	Vector3 GetAstronautPos();
	void AstronautMoveAround();						//The astronaut move around the spaceship in a random amount of steps
	void UpgradeWeapon(int Damage);							//int Damage is from Weapon class		
	int GetWeaponPrice(int Price);							//Get the Price from Weapon class
	void BulletRefill(int BulletsInMagzine,int TotalBullets);//Get the 2 Values from Weapon class
private:
	short BulletPrice;
	Vector3 Position;
};

Astronaut::Astronaut()
{
}

Astronaut::~Astronaut()
{
}






#endif // !ASTRONAUT_H
