#include "Assignment3.h"



void Assignment3::AlienSpawn(double dt)
{
	if ((countdownAlienSpawn.TimeCountDown(dt) <= 0) && (Aliens.size()) < 20 && (f.flagIsBlue == true))
	{
		countdownAlienSpawn.resetTime();
		float spawnAlienz = (rand() % 100 - 50.f);
		short s = rand() % 3;
		if (s == 0)
		{
			Enemy newAlien(Vector3(55.f, 0.f, spawnAlienz), Vector3(camera.position.x, -1.f, camera.position.z), Vector3(0.5f, 1.f, 0.5f), 100, 5, 10, 10);
			Aliens.push_back(newAlien);
		}
		else if (s == 1)
		{
			Enemy newAlien(Vector3(55.f, 0.f, spawnAlienz), Vector3(camera.position.x, -1.f, camera.position.z), Vector3(0.8f, 1.f, 0.8f), 200, 5, 5, 10, 2.0f);
			Aliens.push_back(newAlien);
		}
		else
		{
			Enemy newAlien(Vector3(55.f, 0.f, spawnAlienz), Vector3(camera.position.x, -1.f, camera.position.z), Vector3(0.4f, 1.f, 0.4f), 40, 5, 20, 10, 0.7f);
			Aliens.push_back(newAlien);
		}
	}
}
void Assignment3::AlienSpawnByBoss(double dt ,short AlienType)
{
	countdownAlienSpawnByBoss.TimeCountDown(dt);
	if ((Aliens.size()) < 20 && countdownAlienSpawnByBoss.GetTimeNow() <=0)
	{
		countdownAlienSpawn.resetTime();
		float spwanAlienz = (rand()%10)+3;
		float spwanAlienx = (rand() % 10) + 3;
		if (AlienType == 0)
		{
			Enemy newAlien(Vector3(spwanAlienx, 0.f, spwanAlienz), Vector3(camera.position.x, -1.f, camera.position.z), Vector3(0.5, 1, 0.5), 100, 5, 10, 10);
			Aliens.push_back(newAlien);
		}
		else if (AlienType == 1)
		{
			Enemy newAlien(Vector3(spwanAlienx, 0.f, spwanAlienz), Vector3(camera.position.x, -1.f, camera.position.z), Vector3(0.8, 1, 0.8), 200, 5, 5, 10, 2.0f);
			Aliens.push_back(newAlien);
		}
		else
		{
			Enemy newAlien(Vector3(spwanAlienx, 0.f, spwanAlienz), Vector3(camera.position.x, -1.f, camera.position.z), Vector3(0.25f, 1, 0.25f), 40, 5, 20, 10, 0.7f);
			Aliens.push_back(newAlien);
		}
	}
}
void Assignment3::RockSpawn(double dt)
{
	if (countdownRock.TimeCountDown(dt) <= 0 && Rocks.size() < 10)
	{
		randomx = rand() % 100 - 50.f;
		randomz = rand() % 100 - 50.f;

		if (getMagnitude(Vector3(randomx, -1, randomz), Vector3(camera.position.x, -1, camera.position.z)) >= 20.0f)//spwan 20 units away from the player
		{
			countdownRock.resetTime();
			Rock newRock(Vector3(randomx, -1.f, randomz), rand() % 4 + 1.f);
			Rocks.push_back(newRock);
		}
	}
}

void Assignment3::TurretSpawn()
{
	float cutOff = 1; //used to mutiply camera view to get intersection with 0
	if (camera.target.y <= 0)
	{
		while (TurretPos.y >= -1)
		{
			TurretPos = camera.view * cutOff;
			cutOff += 0.1;
		}
		player.ObtainResources(-50);
		Turret newTurret(100, a.TurretNewDmg, Vector3(TurretPos.x + camera.position.x, 0, TurretPos.z + camera.position.z));
		Turrets.push_back(newTurret);
		countdownTurretSpawn.resetTime();
		TurretPos = (0.f, 0.f, 0.f);//reset the value of the variable
	}
}