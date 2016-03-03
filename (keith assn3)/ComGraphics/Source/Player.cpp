/******************************************************************************/
/*!
\file	Player.h
\author Lim Zhi Yuan
\par	email: 153432K\@mymail.nyp.edu.sg
\brief
Class for the player, stores information of player's status.
*/
/******************************************************************************/

#include"Player.h"

/******************************************************************************/
/*!
\brief
Constructor for Player class

\param hp
Amount of health the Player will have
*/
/******************************************************************************/
Player::Player(const int &hp) : HP(hp)
{
	Resources = 0;
	Retry = 3;
}

/****************************************************************************** /
/*!
\brief
Default destructor for Player class
*/
/******************************************************************************/
Player::~Player()
{

}

/******************************************************************************/
/*!
\brief
A getter function for Player's health.
\return
Returns the amount of health of the player.
*/
/******************************************************************************/
int Player::GetHp()
{
	return HP;
}

/******************************************************************************/
/*!
\brief
A getter function for Player's mining action, determines the angle of the pickaxe
when rendered on screen.
\return
Returns the value of the angle of the pickaxe.
*/
/******************************************************************************/
float Player::getMiningAction()
{
	return MiningAction;
}

/******************************************************************************/
/*!
\brief
A getter function for the angle between the player and a target.

\param view
View vector
\param target
Coordinates of the target

\return
Returns the angle between the player and the target.
*/
/******************************************************************************/
float Player::getAngle(const Vector3 &view, const Vector3 &target)
{
	float magnitudeA = sqrt(pow(view.x, 2) + pow(view.y, 2) + pow(view.z, 2));
	float magnitudeB = sqrt(pow(target.x, 2) + pow(target.y, 2) + pow(target.z, 2));
	float dotProduct = view.x * target.x + view.y * target.y + view.z * target.z;

	float angle = acos(dotProduct / (magnitudeA * magnitudeB));

	return Math::RadianToDegree(angle);
}

/******************************************************************************/
/*!
\brief
A getter function for Player's amount of resources.
\return
Returns the amount of resources the player has.
*/
/******************************************************************************/
int Player::getResources()
{
	return Resources;
}

/******************************************************************************/
/*!
\brief
A setter function for Player's resources
\param amount
Amount to increase the resources by.
*/
/******************************************************************************/
void Player::ObtainResources(int amount)
{
	Resources += amount;
}

/******************************************************************************/
/*!
\brief
A function to decrease the player's health
\param dmg
Amount to decrease the health by.
*/
/******************************************************************************/
void Player::TakeDmg(int dmg)
{
	if (HP - dmg >= 0)
	{
		HP -= dmg;
	}
	else
	{
		HP = 0;
	}
}

/******************************************************************************/
/*!
\brief
A function to increase the player's health
\param recovered
Amount to increase the health by.
*/
/******************************************************************************/
void Player::RecoverHp(int recovered)
{
	HP += recovered;
}

/******************************************************************************/
/*!
\brief
A function to change the angle of the pickaxe.
\param dt
Delta time.
*/
/******************************************************************************/
void Player::WhileMining(const double &dt)
{
	float speed = 500;
	if (isMining == true)
	{
		MiningAction += speed * dt;
		if (MiningAction >= 45.f)
		{
			MiningAction = 45.f;
			isMining = false;
		}
	}
	else
	{
		MiningAction -= speed * dt;
		if (MiningAction <= 0.f)
		{
			MiningAction = 0.f;
		}
	}
}

/******************************************************************************/
/*!
\brief
A function to check if the player is dead.
\retval false
If the player's HP is above 0.
\retval true
If the player's HP is below 0.
*/
/******************************************************************************/
bool Player::isDead()
{
	if (HP > 0)
	{
		return false;
	}
	else
		return true;
}

/******************************************************************************/
/*!
\brief
A function to reduce the player's resources and reset the health. Called when the
player dies(while still having retries) and chooses to respawn.
*/
/******************************************************************************/
void Player::reset()
{
	Resources /= 2;
	HP = 100;
}

/******************************************************************************/
/*!
\brief
A function to reset the player's resources, retries, and HP to their initial
values. Called when the player chooses to restart the game.
*/
/******************************************************************************/
void Player::gameOver()
{
	Resources = 0;
	HP = 100;
	Retry = 3;
	noOfGrenadesHeld = 5;
	WeaponState = 2;
}