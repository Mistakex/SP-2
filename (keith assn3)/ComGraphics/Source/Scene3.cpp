#include "Assignment3.h"

void Assignment3::Scene3Render()
{
	Boss.bossIsSpawned = true;

	modelStack.PushMatrix();
	modelStack.Translate(Boss.position.x, Boss.position.y, Boss.position.z);
	modelStack.Rotate(Boss.findDirection(), 0, 1, 0);
	modelStack.Translate(0, Boss.EnemySize * 0.85, 0);
	modelStack.Scale(Boss.EnemySize, Boss.EnemySize, Boss.EnemySize);
	RenderAlien(Boss.armRotate,Boss.redAlien);
	modelStack.PopMatrix();


	for (int i = 0; i < 10; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Boss.projectiles[i].getPosition().x, Boss.projectiles[i].getPosition().y, Boss.projectiles[i].getPosition().z);
		modelStack.Scale(0.5f, 0.5f, 0.5f);
		RenderMesh(meshList[GEO_BULLET], true);
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