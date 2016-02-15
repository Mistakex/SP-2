#ifndef ASSIGNMENT2_H
#define ASSIGNMENT2_H

#include "Scene.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class Asn2 : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_LIGHTBALL,
		GEO_QUAD,
		GEO_SPHERE,
		GEO_SPHEREBODY,
		GEO_LEG,
		GEO_TAIL,
		GEO_FEET,
		GEO_WINGTOP,
		GEO_WINGPART,
		GEO_BASECYLINDER,
		GEO_BASETORUS,
		GEO_SKY,
		GEO_EYE,
		GEO_EYE_IRIS,
		GEO_EYE_SHINE,
		GEO_EYE_SIDE,
		GEO_MOUTH,
		GEO_DIGIBODY,
		GEO_DIGISIDE,
		GEO_DIGITORUS,
		GEO_DIGISCREEN1,
		GEO_DIGISCREEN2,
		GEO_DIGIBUTTON,
		GEO_DIGIBUTTONLINE,
		GEO_DIGIANTENNA,
		GEO_DIGIEXTRA,
		GEO_EGG,
		GEO_TRANSFORM,
		GEO_AIRSHOT,
		GEO_AIRSHOTTRAIL,
		GEO_TREE,
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
		U_TOTAL,
	};
public:
	Asn2();
	~Asn2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	void RenderMesh(Mesh *mesh, bool enableLight);

	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	float rotateAngle;
	float planet1RotAngle, planet1RevAngle, moon1RotAngle;

	Camera2 camera;

	MS modelStack, viewStack, projectionStack;

	Light light[1];

	bool LightSwitch;
};

#endif