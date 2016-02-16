#ifndef ASSIGNMENT3_H
#define ASSIGNMENT3_H

#include "Scene.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include"CountDown.h"


class Assignment3 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_BOTTOM,
		GEO_TOP,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_FRONT,
		GEO_BACK,
		GEO_QUAD,
		GEO_BULLET,
		GEO_MODEL1,
		GEO_MODEL2,
		GEO_BOULDER,
		GEO_CRATER,
		GEO_LIGHTBALL,
		GEO_TEXT,
		GEO_HELMET,
		GEO_ALIENHEAD,
		GEO_ALIENBODY,
		GEO_ALIENPART,
		GEO_SIGN,
		GEO_TENT,
		GEO_ROCK,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_NUMLIGHTS,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
public:
	Assignment3();
	~Assignment3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderModelOnScreen(Mesh *mesh, bool enableLight, float size, float x, float y);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox();
	void RenderAlien(float armRotate = 0);

	void checkCollision(const Vector3 &center, float x1, float z1, float y1);

	// countdown
	Countdown countdownRock = Countdown(10.0f);


	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];


	Camera3 camera;

	MS modelStack, viewStack, projectionStack;

	Light light[2];
};

#endif