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

	if (Boss.GetShooting() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Boss.projectile.getPosition().x, Boss.projectile.getPosition().y, Boss.projectile.getPosition().z);
		modelStack.Scale(0.5f, 0.5f, 0.5f);
		RenderMesh(meshList[GEO_BULLET], true);
		modelStack.PopMatrix();
	}

	if (Boss.spawnerCounter == 5)
	{
		Boss.spawnerCounter = 0;
		AlienSpawnByBoss(10, 0);
	}

}