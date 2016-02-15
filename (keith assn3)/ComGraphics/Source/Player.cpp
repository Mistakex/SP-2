#include"Player.h"

Player::Player(int hp) : HP(hp)
{
}

Player::~Player()
{

}

int Player::GetHp()
{
	return HP;
}

int Player::GetResources(int amount)
{
	Resources += amount;
}

float Player::WhileMining()
{

}
void Player::TakeDmg(int dmg)
{
	HP -= dmg;
}

void Player::RecoverHp(int recovered)
{
	HP += recovered;
}

void Player::changeWeapon(char weapon)
{
	WeaponState = weapon;
}

char Player::getWeaponState()
{
	return WeaponState;
}