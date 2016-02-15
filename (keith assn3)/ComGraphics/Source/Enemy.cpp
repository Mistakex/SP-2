#include "Enemy.h"



Enemy::Enemy(int hp, int attack, int movespeed, Vector3 pos, int range) : Hp(100), AttackDamage(5), Movespeed(10)
{
	EnemyPos = pos;
	this->range = range;
}

Enemy::~Enemy()
{
}

int Enemy::GetEnemyHp()
{
	return Hp;
}

int Enemy::GetEnemyAtt()
{
	return AttackDamage;
}

int Enemy::GetMovespeed()
{
	return MoveSpeed;
}

short Enemy::GetResources()
{
	return Resources;
}

float Enemy::GetDistance()
{
	Vector3 view = target - EnemyPos;
	return sqrt(pow(view.x, 2) + pow(view.y, 2) + pow(view.z, 2));
}

void Enemy::EnemyMove(double dt)
{
	Vector3 view = target - EnemyPos;
	if (GetDistance() >= range )
	{
		EnemyPos = EnemyPos - view*dt;
	}
}

void Enemy::EnemyTakeDmg(int Dmg)
{
	Hp -= Dmg;
}

void Enemy::EnemyShootAt()
{
}

bool Enemy::InRangeOfPlayer()
{
	if (GetDistance() >= range)
	{
		return false;
	}
	else
		return true;
}

bool Enemy::isDead()
{
	if (Hp <= 0)
	{
		return true;
	}
	else
		return false;
}