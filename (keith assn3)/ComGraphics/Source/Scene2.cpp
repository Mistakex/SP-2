/******************************************************************************/
/*!
\file	Grenade.cpp
\author 
\par	email: 
\brief
scene2 updates
*/
/******************************************************************************/
#include "Assignment3.h"

/******************************************************************************/
/*!
\brief	Empty all the Vector
\param dt
delta time
*/
/******************************************************************************/
void Assignment3::EmptyVector()
{
	while (Aliens.empty() == false)
	{
		Aliens.pop_back();
	}
	while (Rocks.empty() == false)
	{
		Rocks.pop_back();
	}
	while (Turrets.empty() == false)
	{
		Turrets.pop_back();
	}
	while (Pillars.empty() == false)
	{
		Pillars.pop_back();
	}
	while (gameState == GS_SCENE2 && a.Harvestor.empty() == false)
	{
		a.Harvestor.pop_back();
	}
}
/******************************************************************************/
/*!
\brief	Render the dome
\param scale
scaling for the dome
\param x
x coordinate
\param y
y coordinate
\param z
z coordinate
*/
/******************************************************************************/
void Assignment3::RenderDome(float scale, float x, float y, float z)
{
	modelStack.PushMatrix();
	modelStack.Translate(x, y, z);
	modelStack.Scale(scale, scale, scale);
	RenderMesh(meshList[GEO_DOME], false);
	modelStack.PopMatrix();
}
/******************************************************************************/
/*!
\brief	Update for scene2
*/
/******************************************************************************/
void Assignment3::Scene2Updates()
{
	if (camera.position.x < 5.5f &&camera.position.x >-5.5f && camera.position.z > 17 && camera.position.z < 26)
	{
		gameState = GS_SCENE3;
		camera.position.Set(0, 0, 68);
		EmptyVector();
		Pillars.push_back(CollisionObject(Vector3(30, 0, 30), 5.f));
		Pillars.push_back(CollisionObject(Vector3(-30, 0, -30), 5.f));
		Pillars.push_back(CollisionObject(Vector3(-30, 0, 30), 5.f));
		Pillars.push_back(CollisionObject(Vector3(30, 0, -30), 5.f));
		sound.playSoundThreaded("Music/bossfight.mp3");
	}
}