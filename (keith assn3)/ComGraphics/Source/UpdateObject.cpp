#include "Assignment3.h"


void Assignment3::TurretUpdate(double dt)
{
	for (size_t i = 0; i < Turrets.size(); i++)
	{
		if (Aliens.empty() == true && Boss.isDead() == true)
		{
			Turrets[i].bulletPos = (0, -10, 0);
		}
		if (Aliens.empty() == true && Boss.isDead() ==false && gameState == GS_SCENE3)
		{
			Turrets[i].LookAtEnemy(Boss);
			Turrets[i].TargetEnemy(Boss.position);
			Turrets[i].ShootAtEnemy(dt);
			if (Turrets[i].shooting == true)
			{
				if (getMagnitude(Turrets[i].bulletPos, Turrets[i].Target) <= 1.0f && Turrets[i].hit == false)
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
					Turrets[i].LookAtEnemy(Aliens[s]);
					Turrets[i].TargetEnemy(Aliens[s].position);
					Turrets[i].ShootAtEnemy(dt);
					if (Turrets[i].shooting == true)
					{
						if (getMagnitude(Turrets[i].bulletPos, Turrets[i].Target) <= 1.0f && Turrets[i].hit == false)
						{
							Turrets[i].hit = true;
							Aliens[s].EnemyTakeDmg(Turrets[i].GetDamage());
						}
					}
					break;
				}
				else if (Turrets[i].shooting == true)
				{
					Turrets[i].bulletPos = Turrets[i].GetPosition();
					Turrets[i].bulletPos.y = -0.5f;
				}
				s++;
			}
		}
		else
		{
			Turrets[i].bulletPos = Turrets[i].GetPosition();
			Turrets[i].bulletPos.y = -0.5f;
		}
	}
}
void Assignment3::AlienUpdate(double dt)
{
	for (vector<Enemy>::iterator it = Aliens.begin(); it != Aliens.end();)
	{
		(*it).update(camera, dt, &player);
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