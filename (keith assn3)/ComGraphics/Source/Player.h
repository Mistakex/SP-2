
/******************************************************************************/
/*!
\file	Player.h
\author Lim Zhi Yuan
\par	email: 153432K\@mymail.nyp.edu.sg
\brief
Class for the player, stores information of player's status.
*/
/******************************************************************************/
#ifndef PLAYER_H
#define PLAYER_H

#include "Vector3.h"
#include "Music.h"

/******************************************************************************/
/*!
Class Player:
\brief	Player class
*/
/******************************************************************************/

class Player
{
public:
	Player(const int &hp);
	~Player();
	
	// getters
	int GetHp();
	float getMiningAction();
	float getAngle(const Vector3 &view, const Vector3 &target);
	int getResources();
	
	// setters
	void ObtainResources(int amount); // increase resources
	void TakeDmg(int dmg);
	void RecoverHp(int recovered);

	// other functions
	void WhileMining(const double &dt);	//increase and decrease the value for MiningAction
	bool isDead();
	void reset();
	void gameOver();

	bool isMining;
	int Retry;
	int WeaponState;		//which weapon u using
	int noOfGrenadesHeld = 0;

private:
	int HP;
	int Resources;
	float MiningAction;		//waving your pickaxe in da air
	
};
#endif // !PLAYER_H
