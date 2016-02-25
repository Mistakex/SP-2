#include "Assignment3.h"

void Assignment3::Scene3Render()
{
	modelStack.PushMatrix();
	modelStack.Translate(Boss.position.x, Boss.position.y, Boss.position.z);
	modelStack.Rotate(Boss.findDirection(), 0, 1, 0);
	modelStack.Translate(0, Boss.EnemySize * 0.85, 0);
	modelStack.Scale(Boss.EnemySize, Boss.EnemySize, Boss.EnemySize);
	RenderAlien(Boss.armRotate);
	modelStack.PopMatrix();
}