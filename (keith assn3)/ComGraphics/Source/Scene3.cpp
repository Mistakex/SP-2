#include "Assignment3.h"
#include "Music.h"

void Assignment3::Scene3Render()
{
	Boss.bossIsSpawned = true;

	RenderDome(40, 0, -1, 0);

	if (Boss.GetEnemyHp() > 0)
	{	
		modelStack.PushMatrix();
		modelStack.Translate(Boss.position.x, Boss.position.y, Boss.position.z);
		modelStack.Rotate(Boss.findDirection(), 0, 1, 0);
		modelStack.Translate(0, Boss.EnemySize * 0.85f, 0);
		modelStack.Scale(Boss.EnemySize, Boss.EnemySize, Boss.EnemySize);
		RenderAlien(Boss.armRotate, Boss.redAlien);
		modelStack.PopMatrix();

		for (int i = 0; i < 10; ++i)
		{
			modelStack.PushMatrix();
			modelStack.Translate(Boss.projectiles[i].getPosition().x, Boss.projectiles[i].getPosition().y, Boss.projectiles[i].getPosition().z);
			modelStack.Scale(0.5f, 0.5f, 0.5f);
			RenderMesh(meshList[GEO_BULLET], true);
			modelStack.PopMatrix();
		}
	}

	for (vector<CollisionObject>::iterator it = Pillars.begin(); it != Pillars.end(); ++it)
	{
		modelStack.PushMatrix();
		modelStack.Translate(it->position.x, it->position.y, it->position.z);
		modelStack.Scale(it->circleRange, 10, it->circleRange);
		RenderMesh(meshList[GEO_PILLAR], true);
		modelStack.PopMatrix();
	}



	if (Boss.spawnerCounter >= 50)
	{
		if (Boss.spawnDelay > 0.3f && Aliens.size() < 10)
		{
			AlienSpawnByBoss(10, 0);
			Boss.spawnDelay = 0.f;
		}
	}
}

void Assignment3::Scene3Updates()
{
	for (int i = 0; i < sizeof(Boss.projectiles) / sizeof(Boss.projectiles[0]); ++i)
	{
		for (unsigned int j = 0; j < Pillars.size(); ++j)
		{
			if (getMagnitude(Boss.projectiles[i].getPosition(), Pillars[j].position) < Pillars[j].circleRange)
			{
				Boss.projectiles[i].setView(Vector3(0, 0, 0));
			}
		}
	}
	for (unsigned int i = 0; i < Aliens.size(); ++i)
	{
		for (unsigned int j = 0; j < Pillars.size(); ++j)
		{
			if (getMagnitude(Aliens[i].projectile.getPosition(), Pillars[j].position) < Pillars[j].circleRange)
			{
				Aliens[i].projectile.setView(Vector3(0, 0, 0));
			}
		}
	}
}

void Assignment3::Scene3UI()
{
	if (Boss.GetEnemyHp() <= 0)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "YOU WIN!", Color(1, 0, 0), 10.f, 2.75f, 2.5f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'P' to pause and restart", Color(1, 0, 0),2, 16.f, 10.f);
		modelStack.PopMatrix();
	}
}