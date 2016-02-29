#ifndef PLAYER_H
#define PLAYER_H

#include "Vector3.h"

class Player
{
public:
	Player(const int &hp);
	~Player();
	int noOfRetry();
	int Retry;
	int GetHp();
	int ObtainResources(int amount); // increase resources


	void WhileMining(const double &dt);	//increase and decrease the value for MiningAction
	float getMiningAction();
	void TakeDmg(int dmg);
	void RecoverHp(int recovered);
	void changeWeapon(int weapon);
	int getResources();
	bool isDead();
	float getAngle(const Vector3 &view, const Vector3 &target);
	void reset();
	void gameOver();

	int BulletsInMagzine;
	int TotalBullets;		//Reloading
	bool sprint;			//running or not
	bool isMining;
	int WeaponState;		//which weapon u using
	int noOfGrenadesHeld = 0;

private:
	int HP;
	int Resources;
	float MiningAction;		//waving your pickaxe in da air
	
};
#endif // !PLAYER_H
