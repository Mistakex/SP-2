/******************************************************************************/
/*!
\file	Enemy.cpp
\author Cheng Zi Wei Keith
\par	email: 152639K@mymail.nyp.edu.sg
\brief
Enemies shooting and finding their way to the player, including the boss
*/
/******************************************************************************/

#include "Enemy.h"

/******************************************************************************/
/*!
\brief	
Default constructor for enemy class
*/
/******************************************************************************/

Enemy::Enemy()
{
}

/******************************************************************************/
/*!
\brief	
Constructor for Enemy class

\param	pos
Enemy position
\param	target
Enemy target
\param	range
The collision range of the enemy for the bullets from weapons
\param	hp
Health of the enemy
\param	attack
Attack damage of enemy
\param	movespeed
Movement speed of enemy
\param range2
The range of which the enemy will follow the player until it starts shooting
\param size
The size of the enemy
\param Boss
To check whether the enemy will follow the patterns of a boss or a regular enemy
*/
/******************************************************************************/

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

/******************************************************************************/
/*!
\brief	
Default destructor for enemy class
*/
/******************************************************************************/

Enemy::~Enemy()
{
}

/******************************************************************************/
/*!
\brief	
A getter function for enemy hp
\return
Returns the health of the enemy
*/
/******************************************************************************/

int Enemy::GetEnemyHp()
{
	return Hp;
}

/******************************************************************************/
/*!
\brief	
A getter function for enemy attack damage
\return
Returns the attack damage of the enemy
*/
/******************************************************************************/

int Enemy::GetEnemyAtt()
{
	return AttackDamage;
}

/******************************************************************************/
/*!
\brief	
A getter function for enemy movement speed
\return
Returns the attack damage of the enemy
*/
/******************************************************************************/

int Enemy::GetMovespeed()
{
	return MoveSpeed;
}

/******************************************************************************/
/*!
\brief	
A getter function for enemy resources
\return
Returns the resources the enemy will drop
*/
/******************************************************************************/

short Enemy::GetResources()
{
	return Resources;
}

/******************************************************************************/
/*!
\brief	
Finds the distance between the enemy and the target of the enemy
\return
Returns the distance between target and enemy
*/
/******************************************************************************/

float Enemy::GetDistance()
{
	Vector3 view = target - position;
	return sqrt(pow(view.x, 2) + pow(view.y, 2) + pow(view.z, 2));
}

/******************************************************************************/
/*!
\brief	
Checks whether the enemy is currently shooting
\return 
Returns whether the enemy is currently shooting or not
*/
/******************************************************************************/

bool Enemy::GetShooting()
{
	return Shooting;
}

/******************************************************************************/
/*!
\brief	
The code for movement and shooting of enemy and boss is all run here. 
\param dt
The time in between each frame
\param *p
The player. Used for checking collision between player and the enemy bullet, allowing the player health to be updated
\param *Turrets
Used for checking collision between the turrets and the enemy bullet, allowing the turrets health to be updated
*/
/******************************************************************************/

void Enemy::EnemyMove(double dt, Player *p, vector<Turret> *Turrets)
{
	fireDelay += (float)dt;

	Vector3 view = Vector3(0, 0, 0);
	if (target != position)
		view = (target - position).Normalized();
		
	if (!isBoss)
	{
		if (GetDistance() > range + KiteTimer)
		{
			position += Vector3(view.x,0.f,view.z)*(float)MoveSpeed*(float)dt;
			if (Shooting == true)
			{
				if (armRotate > 0)
					armRotate -= (float)(90 * dt);
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
			BossShootAt(dt, 0.1f, 0.2f);
		}
		else
		{
			if (armRotate > 0)
				armRotate -= (float)(90 * dt);
			BossSpawnMinions(dt);
		}
	}
}

/******************************************************************************/
/*!
\brief	
Damage taken by enemy. Turns the enemy red when damage is taken
\exception
When hp after damage taken is below 0, Hp defaults to 0
\param
The damage taken by the enemy.
*/
/******************************************************************************/

void Enemy::EnemyTakeDmg(int Dmg)
{
	redAlien = true;
	if (Hp - Dmg >= 0)
		Hp -= Dmg;
	else
		Hp = 0;
}

/******************************************************************************/
/*!
\brief	Changes the Hp of the enemy
\param Hp
The amount of Hp that the enemy is set to
*/
/******************************************************************************/

void Enemy::EnemySetHp(const int &Hp)
{
	this->Hp = Hp;
}

/******************************************************************************/
/*!
\brief	Code for the boss spawning minions. This is run when the boss's spawnerCounter reaches 50
\param dt
The amount of time in between each frame
*/
/******************************************************************************/

void Enemy::BossSpawnMinions(const double &dt)
{
	spawnDelay += (float)dt;
	float speed = 5;
	if (position.y < 10 && startSpawningMinions)
	{
		position.y += speed * (float)dt;
	}
	else
	{
		startSpawningMinions = false;
		position.y -= (float)(speed * dt);
		if (position.y <= 0)
		{
			position.y = 0;
			spawnerCounter = 0;
		}
	}
}

/******************************************************************************/
/*!
\brief	Code for the enemy shooting. The enemy raises its arms, shoots a bullet, then lowers its arms.
\param dt
The amount of time in between each frame
\param startShooting
The amount of time before the enemy starts raising its arms
\param endShooting
The amount of time before the entire shooting animations ends
\param bulletSpeed
The speed of the bullet
\param *p
The player, allowing for checking of bullet collision and updating the player hp
\param *Turrets
The turrets, allowing for checking of bullet collision and updating the turrets hp
*/
/******************************************************************************/

void Enemy::EnemyShootAt(const double &dt, const float &startShooting, const float &endShooting, const float &bulletSpeed, Player *p, vector<Turret> *Turrets)
{
	if (fireDelay < startShooting)
	{
		if (Shooting == true)
		{
			if (armRotate > 0)
				armRotate -= (float)(90 * dt);
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
			armRotate += (float)(90 * dt);
		}
		Shooting = false;
	}
}

/******************************************************************************/
/*!
\brief	Code for the boss shooting. The enemy raises its arms, shoots a bullet
\param dt
The amount of time in between each frame
\param startShooting
The amount of time before the enemy starts raising its arms
\param endShooting
The amount of time before the entire shooting animations ends
*/
/******************************************************************************/

void Enemy::BossShootAt(const double &dt, const float &startShooting, const float &endShooting)
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
			armRotate += (float)(90 * dt);
		}
		Shooting = false;
	}
}

/******************************************************************************/
/*!
\brief	Code for finding the angle between the enemy and the target
\return
The angle between the enemy and target of enemy
*/
/******************************************************************************/

float Enemy::findDirection()
{
	Vector3 view = target - position;
	if (target.z > position.z)
		return Math::RadianToDegree(atan(view.x / view.z)) - 180;
	else
		return Math::RadianToDegree(atan(view.x / view.z));
}

/******************************************************************************/
/*!
\brief	The enemy kites the player by moving left and right in this function
\param dt
The time in between each frame
*/
/******************************************************************************/

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
			position += right*((float)MoveSpeed / 4.f)*(float)dt;
		else
			position -= right*((float)MoveSpeed / 4.f)*(float)dt;
	}
}

/******************************************************************************/
/*!
\brief	Checks whether the enemy is in range of the player to shoot him
\return
Returns true if the enemy is in range of the player and false if it is not in range
*/
/******************************************************************************/

bool Enemy::InRangeOfPlayer()
{
	if (GetDistance() >= range)
	{
		return false;
	}
	else
		return true;
}

/******************************************************************************/
/*!
\brief	Checks whether the enemy is dead or not
\return
Returns true if the enemy has Hp lesser than or equals to 0 and false if it has more than 0 Hp
*/
/******************************************************************************/

bool Enemy::isDead()
{
	if (Hp <= 0)
	{
		return true;
	}
	else
		return false;
}

/******************************************************************************/
/*!
\brief	Updates the enemy's target every frame and makes the enemy move
\param camera
Used to get camera position to get the player's position
\param dt
Time in between each frame
\param *p
Used to run the EnemyMove function to move the enemy
\param *Turrets
Used to run the EnemyMove function to move the enemy
*/
/******************************************************************************/

void Enemy::update(Camera3 camera,const double &dt, Player *p,vector<Turret> *Turrets)
{
	if (redAlien)
	{
		redTimer += (float)dt;
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

/******************************************************************************/
/*!
\brief	Used to check for collision between the enemy's bullet and the player or turret
\param *p
Used to update the player's health if there is collision
\param *Turrets
Used to update the turret's health if there is collision
\return
Returns true if there is collision and returns false if there is no collision
*/
/******************************************************************************/

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

/******************************************************************************/
/*!
\brief	Used to check for collision between the bosses bullet and the player or turret
\param *p
Used to update the player's health if there is collision
\param *Turrets
Used to update the turret's health if there is collision
\return
Returns true if there is collision and returns false if there is no collision
*/
/******************************************************************************/

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