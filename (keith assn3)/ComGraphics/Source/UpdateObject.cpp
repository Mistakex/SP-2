#include "Assignment3.h"


void Assignment3::TurretUpdate(double dt)
{
	for (size_t i = 0; i < Turrets.size(); i++)
	{
		if (Aliens.empty() == true && Boss.isDead() == true)
		{
			Turrets[i].bullet.updatePosition(Vector3(0, -10, 0));
		}
		else if (Aliens.empty() == true && Boss.isDead() ==false && gameState == GS_SCENE3)
		{
			Turrets[i].LookAtEnemy(Boss);
			Turrets[i].TargetEnemy(Boss.position);
			Turrets[i].ShootAtEnemy(dt);
			if (Turrets[i].shooting == true)
			{
				if (getMagnitude(Turrets[i].bullet.getPosition(), Turrets[i].Target) <= 1.0f && Turrets[i].hit == false)
				{
					Turrets[i].hit = true;
					Boss.EnemyTakeDmg(Turrets[i].GetDamage());
				}
			}
		}
		else if (Aliens.empty() == false)
		{
			size_t s = 0;
			while (s < Aliens.size())
			{
				if (getMagnitude(Turrets[i].GetPosition(), Aliens[s].position) <= 15.f)
				{
					Turrets[i].TargetEnemy(Aliens[s].position);
					Turrets[i].LookAtEnemy(Aliens[s]);
					Turrets[i].ShootAtEnemy(dt);

					if (getMagnitude(Turrets[i].bullet.getPosition(), Turrets[i].Target) <= 1.0f && Turrets[i].hit == false)
					{
						Turrets[i].hit = true;
						Aliens[s].EnemyTakeDmg(Turrets[i].GetDamage());
					}

					break;
				}
				else
				{
					Turrets[i].bullet.moveBullet(dt, Turrets[i].BulletSpeed);
				}
				s++;
			}
		}
		else
		{
			Turrets[i].bullet.updatePosition(Turrets[i].GetPosition() - Vector3(0, 0.5, 0));
		}
	}


	for (vector<Turret>::iterator it = Turrets.begin(); it != Turrets.end();)
	{
		if (it->Hp == 0)
		{
			it = Turrets.erase(it);
		}
		else
		{
			++it;
		}
	}
}
void Assignment3::AlienUpdate(double dt)
{
	for (vector<Enemy>::iterator it = Aliens.begin(); it != Aliens.end();)
	{
		(*it).update(camera, dt, &player,&Turrets);
		if ((*it).isDead())
		{
			Alienresources = rand() % 15 + 5;
			KillMessage.resetTime();
			player.ObtainResources(Alienresources);
			it = Aliens.erase(it);
		}
		else
		{
			++it;
		}
	}
}
void Assignment3::HarvestorUpdate(double dt)
{
	if (a.Harvestor.empty() == false && Rocks.empty() == false)
	{
		for (unsigned int i = 0; i < a.Harvestor.size(); i++)
		{
			a.Harvestor[i].MoveTowards(Rocks[0].position, dt);
			if (getMagnitude(a.Harvestor[i].Position, Rocks[0].position) <= 4)
			{
				a.Harvestor[i].MineRocks(Rocks[0], player);
				if (Rocks[0].Size <= 0)
				{
					Rocks.erase(Rocks.begin());
					break;
				}
			}
		}
	}
}
void Assignment3::GrenadeUpdate(double dt)
{
	if (GrenadesFlying.empty() == false)
	{
		for (unsigned int i = 0; i < GrenadesFlying.size(); i++)
		{
			GrenadesFlying[i].ThrowGrenade(dt);
		}
		if (GrenadesFlying[0].throwGrenade.GetTimeNow() <= 0.2)
		{
			GrenadesFlying[0].Explode = true;
			GrenadesFlying[0].GetExplosion();
		}
		if (GrenadesFlying[0].throwGrenade.GetTimeNow() <= 0)
		{
			for (unsigned int i = 0; i < Aliens.size(); i++)
			{
				GrenadesFlying[0].DealDamage(Aliens[i]);
			}
			if (Boss.isDead() == false && gameState == GS_SCENE3)
			{
				GrenadesFlying[0].DealDamage(Boss);
			}
			sound.playSoundThreaded("Music/explosion.wav");
			GrenadesFlying.erase(GrenadesFlying.begin());
		}
	}
}
void Assignment3::MiningUpdate()
{
	vector<Rock>::iterator i = Rocks.begin();
	while (i != Rocks.end())
	{
		if ((getMagnitude(Vector3((*i).position.x, -1, (*i).position.z), Vector3(camera.position.x, camera.position.y - 1, camera.position.z)) - (*i).Size * 2.f) < 0
			&& player.getAngle(camera.view, Vector3((*i).position.x, -1, (*i).position.z) - camera.position) < 45.f)
		{
			if (player.isMining == false)
			{
				player.isMining = true;
				sound.playSoundThreaded("Music/mining.wav");
				resourceOfRock = (*i).GetResources();
				player.ObtainResources(resourceOfRock);
				(*i).ReduceSize();
			}
			if ((*i).Size <= 0)
			{
				Rocks.erase(i);
			}
			countdownMining.resetTime();
			break;
		}
		else{ i++; }
	}
}