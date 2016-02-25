#include "Assignment3.h"


void Assignment3::RenderDome(float scale, float x, float y, float z)
{
	modelStack.PushMatrix();
	modelStack.Translate(x, y, z);
	modelStack.Scale(scale, scale, scale);
	RenderMesh(meshList[GEO_DOME], false);
	modelStack.PopMatrix();
}
void Assignment3::Scene2Updates()
{
	if (camera.position.x <1.5f &&camera.position.x >-1.5f && camera.position.z > 18 && camera.position.z < 19)
	{
		gameState = GS_SCENE3;
		camera.position.Set(0, 0, 70);
		light[0].type = Light::LIGHT_POINT;
		light[0].position.Set(0,30.0f, 0);
		light[0].power = 10.0f;
	}
}