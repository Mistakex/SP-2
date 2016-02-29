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
			short s = 0;
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