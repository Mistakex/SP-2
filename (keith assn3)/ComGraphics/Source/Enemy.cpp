#include "Enemy.h"

Enemy::Enemy()
{
}

Enemy::Enemy(Vector3 pos,Vector3 tar, Vector3 range, int hp, int attack, int movespeed,int range2,float size,bool Boss) : Hp(hp), AttackDamage(attack), MoveSpeed(movespeed)
{
	position = pos;
	target = tar;
	rangexyz = range;
	this->range = range2;
	KiteTimer = 0;
	Shooting = false;
	projectile.setView(Vector3(0, 0, 0));
	fireDelay = 0;
	armRotate = 0;
	EnemySize = size;
	isBoss = Boss;
	spawnerCounter = 0;
	bossIsSpawned = false;
	redAlien = false;
	redTimer = 0;
	currentBullet = 0;
	spawnDelay = 0;
	startSpawningMinions = false;
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
	Vector3 view = target - position;
	return sqrt(pow(view.x, 2) + pow(view.y, 2) + pow(view.z, 2));
}

bool Enemy::GetShooting()
{
	return Shooting;
}

void Enemy::EnemyMove(double dt, Player *p, vector<Turret> *Turrets)
{
	fireDelay += dt;

	Vector3 view = Vector3(0, 0, 0);
	if (target != position)
		view = (target - position).Normalized();
		
	if (!isBoss)
	{
		if (GetDistance() > range + KiteTimer)
		{
			position += Vector3(view.x,0,view.z)*MoveSpeed*dt;
			if (Shooting == true)
			{
				if (armRotate > 0)
					armRotate -= 90 * dt;
				projectile.moveBullet(dt, 70.f);
				checkBulletCollision(p,Turrets);
			}
		}
		else if (KiteTimer < 7)
		{
			EnemyKite(dt);
			EnemyShootAt(dt,2.f,4.f, 10.f,p,Turrets);
		}
		else if (KiteTimer >= 7)
		{
			EnemyShootAt(dt,2.f,4.f, 10.f,p,Turrets);
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
		else
		{
			EnemyShootAt(dt, 2.f, 4.f, 10.f, p,Turrets);
		}
	}
	else
	{
		for (int i = 0; i < sizeof(projectiles) / sizeof(projectiles[0]); ++i)
		{
			projectiles[i].moveBullet(dt, 60.f);
		}
		checkBulletsCollision(p,Turrets);

		if (spawnerCounter < 50)
		{
			BossShootAt(dt, 0.1f, 0.2f, 5.f, p);
		}
		else
		{
			if (armRotate > 0)
				armRotate -= 90 * dt;
			BossSpawnMinions(dt);
		}
	}
}

void Enemy::EnemyTakeDmg(int Dmg)
{
	redAlien = true;
	if (Hp - Dmg >= 0)
		Hp -= Dmg;
	else
		Hp = 0;
}

void Enemy::EnemySetHp(int Hp)
{
	this->Hp = Hp;
}

void Enemy::BossSpawnMinions(const double &dt)
{
	spawnDelay += dt;
	float speed = 5;
	if (position.y < 10 && startSpawningMinions)
	{
		position.y += speed * dt;
	}
	else
	{
		startSpawningMinions = false;
		position.y -= speed * dt;
		if (position.y <= 0)
		{
			position.y = 0;
			spawnerCounter = 0;
		}
	}
}

void Enemy::EnemyShootAt(const double &dt, const float &startShooting, const float &endShooting, const float &bulletSpeed, Player *p, vector<Turret> *Turrets)
{
	if (fireDelay < startShooting)
	{
		if (Shooting == true)
		{
			if (armRotate > 0)
				armRotate -= 90 * dt;
			projectile.moveBullet(dt, 60.f);
			checkBulletCollision(p,Turrets);
		}
		else
		{
			Shooting = true;
			projectile.updatePosition(Vector3(position));
			Vector3 bulletTarget = target + Vector3((rand() % 2) - 0.5f, (rand() % 2) / 2.f - 0.5f, (rand() % 2) / 2.f - 0.5f);
			projectile.setView((bulletTarget - position).Normalized());
		}
	}
	else if (fireDelay >= endShooting)
	{
		fireDelay = 0;
	}
	else
	{
		if (armRotate < 90)
		{
			armRotate += 90 * dt;
		}
		Shooting = false;
	}
}

void Enemy::BossShootAt(const double &dt, const float &startShooting, const float &endShooting, const float &bulletSpeed, Player *p)
{
	if (fireDelay < startShooting)
	{
		if (Shooting == false)
		{
			spawnerCounter++;
			if (spawnerCounter == 50)
			{
				startSpawningMinions = true;
			}
			Shooting = true;
			projectiles[currentBullet].updatePosition(position);
			Vector3 bulletTarget = target + Vector3((rand() % 3) - 1.f, (rand() % 3) - 1.f, (rand() % 3) - 1.f);
			projectiles[currentBullet].setView((bulletTarget - position).Normalized());
			if (currentBullet + 1 < sizeof(projectiles) / sizeof(projectiles[0]))
			{
				currentBullet++;
			}
			else
			{
				currentBullet = 0;
			}
		}
	}
	else if (fireDelay >= endShooting)
	{
		fireDelay = 0;
	}
	else
	{
		if (armRotate < 90)
		{
			armRotate += 90 * dt;
		}
		Shooting = false;
	}
}

float Enemy::findDirection()
{
	Vector3 view = target - position;
	if (target.z > position.z)
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
		if (target != position)
			view = (target - position).Normalized();
		Vector3 right = view.Cross(Vector3(0, 1, 0));
		if (moveRight == true)
			position += right*(MoveSpeed / 4)*dt;
		else
			position -= right*(MoveSpeed / 4)*dt;
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

void Enemy::update(Camera3 camera,const double &dt, Player *p,vector<Turret> *Turrets)
{
	if (redAlien)
	{
		redTimer += dt;
		if (redTimer > 0.3f)
		{
			redAlien = false;
			redTimer = 0.f;
		}
	}
	if (Turrets->empty())
	{
		target = camera.position;
	}
	else
	{
		float minDist = 1000;
		int turretNumber2 = 0;
		for (vector<Turret>::iterator it = (*Turrets).begin(); it != (*Turrets).end(); ++it, ++turretNumber2)
		{
			if (sqrt(pow((it->GetPosition() - position).x, 2) + pow((it->GetPosition() - position).y, 2) + pow((it->GetPosition() - position).z, 2)) < minDist)
			{
				minDist = sqrt(pow((it->GetPosition() - position).x, 2) + pow((it->GetPosition() - position).y, 2) + pow((it->GetPosition() - position).z, 2));
				target = it->GetPosition();
				turretNumber = turretNumber2;
			}
		}
	}
	EnemyMove(dt,p,Turrets);
}

bool Enemy::checkBulletCollision(Player *p, vector<Turret> *Turrets)
{
	float x = 0.5f, y = 1.f, z = 0.5f;
	if ((projectile.getPosition().x > target.x - x && projectile.getPosition().x < target.x + x
		&& projectile.getPosition().y > target.y - y && projectile.getPosition().x < target.y + y
		&& projectile.getPosition().z > target.z - z && projectile.getPosition().z < target.z + z)
		|| (projectile.getPosition() - target).Length() < 0.70f)
	{
		if (Turrets->empty())
			(*p).TakeDmg(AttackDamage);
		else
		{
			(*Turrets)[turretNumber].ReduceHp(AttackDamage);
			std::cout << (*Turrets)[turretNumber].Hp << std::endl;
		}
		return true;
	}
	return false;
}

bool Enemy::checkBulletsCollision(Player *p, vector<Turret> *Turrets)
{
	float x = 0.5f, y = 1.f, z = 0.5f;
	bool hit = false;
	for (int i = 0; i < sizeof(projectiles) / sizeof(projectiles[0]); ++i)
	{
		if ((projectiles[i].getPosition().x > target.x - x && projectiles[i].getPosition().x < target.x + x
			&& projectiles[i].getPosition().y > target.y - y && projectiles[i].getPosition().x < target.y + y
			&& projectiles[i].getPosition().z > target.z - z && projectiles[i].getPosition().z < target.z + z)
			|| (projectiles[i].getPosition() - target).Length() < 0.70f)
		{
			if (Turrets->empty())
				(*p).TakeDmg(AttackDamage);
			else
			{
				(*Turrets)[turretNumber].ReduceHp(AttackDamage);
				std::cout << (*Turrets)[turretNumber].Hp << std::endl;
			}
			hit = true;
		}
	}
	return hit;
}