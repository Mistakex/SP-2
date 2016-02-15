#include "Enemy.h"



Enemy::Enemy(Vector3 pos,Vector3 tar, int hp, int attack, int movespeed, int range) : Hp(hp), AttackDamage(attack), MoveSpeed(movespeed)
{
	EnemyPos = pos;
	target = tar;
	this->range = range;
	KiteTimer = 0;
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
	Vector3 view = Vector3(0, 0, 0);
	if (target != EnemyPos)
		view = (target - EnemyPos).Normalized();
		
	if (GetDistance() > range + KiteTimer)
	{
		EnemyPos += Vector3(view.x,0,view.z)*MoveSpeed*dt;
	}
	else if (KiteTimer < 10)
	{
		EnemyKite(dt);
	}
	else if (KiteTimer >= 10)
	{
		KiteTimer = 0;
		if (rand() % 2 == 0)
		{
			moveRight = true;
		}
		else
		{
			moveRight = false;
		}
	}
}

void Enemy::EnemyTakeDmg(int Dmg)
{
	Hp -= Dmg;
}

void Enemy::EnemyShootAt(Vector3 target)
{
	if (target != EnemyPos)
		Vector3 view = (target - EnemyPos).Normalized();
	else
		Vector3 view = Vector3(0, 0, 0);

}

float Enemy::findDirection()
{
	Vector3 view = target - EnemyPos;
	if (target.z > EnemyPos.z)
		return Math::RadianToDegree(atan(view.x / view.z)) - 180;
	else
		return Math::RadianToDegree(atan(view.x / view.z));
}

void Enemy::EnemyKite(double dt)
{
	KiteTimer += dt;
	if (KiteTimer < 3)
	{
		Vector3 view = Vector3(0, 0, 0);
		if (target != EnemyPos)
			view = (target - EnemyPos).Normalized();
		Vector3 right = view.Cross(Vector3(0, 1, 0));
		if (moveRight == true)
			EnemyPos += right*(MoveSpeed / 2)*dt;
		else
			EnemyPos -= right*(MoveSpeed / 2)*dt;
	}
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