#include "Assignment3.h"


void Assignment3::RenderDome(float scale, float x, float y, float z)
{
	modelStack.PushMatrix();
	modelStack.Translate(0, -1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_DOME], true);
	modelStack.PopMatrix();
}