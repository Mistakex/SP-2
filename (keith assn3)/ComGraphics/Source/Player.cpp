#include"Player.h"
#include "Music.h"

Player::Player(const int &hp) : HP(hp)
{
	Resources = 0;
	Retry = 3;
}

Player::~Player()
{

}

int Player::noOfRetry()
{
	Retry = 3;
	return Retry;
}

int Player::GetHp()
{
	return HP;
}

int Player::ObtainResources(int amount)
{
	Resources += amount;
	return Resources;
}

float Player::getMiningAction()
{
	return MiningAction;
}

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

void Player::RecoverHp(int recovered)
{
	HP += recovered;
}

void Player::changeWeapon(int weapon)
{
	WeaponState = weapon;
}

int Player::getResources()
{
	return Resources;
}

float Player::getAngle(const Vector3 &view, const Vector3 &target)
{
	float magnitudeA = sqrt(pow(view.x, 2) + pow(view.y, 2) + pow(view.z, 2));
	float magnitudeB = sqrt(pow(target.x, 2) + pow(target.y, 2) + pow(target.z, 2));
	float dotProduct = view.x * target.x + view.y * target.y + view.z * target.z;

	float angle = acos(dotProduct / (magnitudeA * magnitudeB));

	return Math::RadianToDegree(angle);
}

bool Player::isDead()
{
	if (HP > 0)
	{
		return false;
	}
	else
		return true;
}

void Player::reset()
{
	Resources /= 2;
	HP = 100;
}