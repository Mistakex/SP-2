#include "Assignment3.h"

void Assignment3::RenderPole()
{
	modelStack.PushMatrix();
	modelStack.Scale(1.5, 2, 1.5);
	modelStack.PushMatrix();
	modelStack.Scale(2, 2, 2);
	modelStack.Translate(0, f.position.y - 1, f.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_FLAGPOLE], true);
	modelStack.PopMatrix();
}
void Assignment3::RenderFlag()
{
	if (!f.flagIsBlue)
	{
		modelStack.PushMatrix();
		modelStack.Scale(2, 2, 2);
		modelStack.Translate(1.5, f.flagheight, f.position.z);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_ENEMYFLAG], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Scale(5, 2, 5);
		modelStack.Translate(0, f.position.y - 1, f.position.z);
		RenderMesh(meshList[GEO_UNCAPTURED], true);
		modelStack.PopMatrix();
	}
	else
	{
		modelStack.PushMatrix();
		modelStack.Scale(2, 2, 2);
		modelStack.Translate(1.5, f.flagheight, f.position.z);
		modelStack.Rotate(90, 0, 1, 0);
		RenderMesh(meshList[GEO_ALLYFLAG], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Scale(5, 2, 5);
		modelStack.Translate(0, f.position.y - 1, f.position.z);
		RenderMesh(meshList[GEO_CAPTURED], true);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();
}
void Assignment3::RenderAlien(float armRotate,bool isRed)
{
	modelStack.PushMatrix();
	modelStack.Translate(0.f, -3.2f, 0.f);
	if (isRed)
	{
		RenderMesh(meshList[GEO_ALIENHEADred], true);
		RenderMesh(meshList[GEO_ALIENBODYred], true);
	}
	else
	{
		RenderMesh(meshList[GEO_ALIENHEAD], true);
		RenderMesh(meshList[GEO_ALIENBODY], true);
	}
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 2.9f, 0.f);
	modelStack.Rotate(armRotate, 1, 0, 0);
	modelStack.Translate(0.f, -2.9f, 0.f);
	modelStack.PushMatrix(); // arms
	modelStack.Translate(-0.3f, 2.7f, 0.f);
	modelStack.Scale(0.2f, 0.4f, 0.4f);
	if (isRed)
	{
		RenderMesh(meshList[GEO_ALIENPARTred], true);
	}
	else
	{
		RenderMesh(meshList[GEO_ALIENPART], true);
	}
	modelStack.PushMatrix();
	modelStack.Translate(3, 0, 0);
	if (isRed)
	{
		RenderMesh(meshList[GEO_ALIENPARTred], true);
	}
	else
	{
		RenderMesh(meshList[GEO_ALIENPART], true);
	}
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}
void Assignment3::RenderCraters()
{
	for (int i = 0; i < 3; ++i)
	{
		if (i == 0)
		{
			modelStack.PushMatrix();
			modelStack.Translate(0, -0.5, 0);
			modelStack.Scale(2, 2, 2);
			RenderMesh(meshList[GEO_CRATER], true);
			modelStack.PopMatrix();
		}
		else if (i == 1)
		{
			modelStack.PushMatrix();
			modelStack.Translate(30, -0.5, 5);
			modelStack.Scale(3, 2, 3);
			RenderMesh(meshList[GEO_CRATER], true);
			modelStack.PopMatrix();
		}
		else
		{
			for (int j = 0; j < 2; ++j)
			{
				modelStack.PushMatrix();
				modelStack.Translate(-20.f, -0.5f, 10.f - j * 20.f);
				modelStack.Scale(3, 2, 3);
				RenderMesh(meshList[GEO_CRATER], true);
				modelStack.PopMatrix();
			}
		}
	}
}
void Assignment3::RenderTurret()
{
	for (size_t i = 0; i < Turrets.size(); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Turrets[i].GetPosition().x, Turrets[i].GetPosition().y - 1, Turrets[i].GetPosition().z);
		modelStack.Scale(0.3f, 0.3f, 0.3f);
		RenderMesh(meshList[GEO_TURRETBASE], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(Turrets[i].GetPosition().x, Turrets[i].GetPosition().y - 0.7f, Turrets[i].GetPosition().z);
		modelStack.Rotate(Turrets[i].turretRotation, 0, 1, 0);
		modelStack.Scale(0.3f, 0.3f, 0.3f);
		RenderMesh(meshList[GEO_TURRETHEAD], true);
		modelStack.PopMatrix();

		if (Turrets[i].GetShooting() == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(Turrets[i].bullet.getPosition().x, Turrets[i].bullet.getPosition().y, Turrets[i].bullet.getPosition().z);
			modelStack.Scale(0.1f, 0.1f, 0.1f);
			RenderMesh(meshList[GEO_BULLET], true);
			modelStack.PopMatrix();
		}
	}
}
void Assignment3::RenderAliens()
{
	for (size_t i = 0; i < Aliens.size(); ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Aliens[i].position.x, Aliens[i].position.y, Aliens[i].position.z);
		modelStack.Rotate(Aliens[i].findDirection(), 0, 1, 0);
		modelStack.Scale(Aliens[i].EnemySize, 1, Aliens[i].EnemySize);
		RenderAlien(Aliens[i].armRotate,Aliens[i].redAlien);
		modelStack.PopMatrix();

		if (Aliens[i].GetShooting() == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(Aliens[i].projectile.getPosition().x, Aliens[i].projectile.getPosition().y, Aliens[i].projectile.getPosition().z);
			modelStack.Scale(0.1f, 0.1f, 0.1f);
			RenderMesh(meshList[GEO_BULLET], true);
			modelStack.PopMatrix();
		}
	}
}
void Assignment3::RenderAstronaut()
{
	modelStack.PushMatrix();
	modelStack.Translate(a.GetAstronautPos().x, a.GetAstronautPos().y, a.GetAstronautPos().z);
	modelStack.Scale(0.3f, 0.3f, 0.3f);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_ASTRONAUT], true);
	modelStack.PopMatrix();
}