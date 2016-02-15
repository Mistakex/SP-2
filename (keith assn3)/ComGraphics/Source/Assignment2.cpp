#include "Assignment2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "Utility.h"

Asn2::Asn2()
{
}


Asn2::~Asn2()
{
}

void Asn2::Init()
{
	LightSwitch = true;
	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.f, 0.2f, 0.2f, 0.f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	glUseProgram(m_programID);

	light[0].position.Set(0, 40, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 30;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;

	// Pass information
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

	//variable to rotate geometry
	rotateAngle = 0;

	//Initialize camera settings
	camera.Init(Vector3(-50, 60, 60), Vector3(0, 0, 0), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1.f, 0.5f, 0.f), 20, 30, 0.55f);
	meshList[GEO_SPHERE]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_SPHERE]->material.kShininess = 0.3f;

	meshList[GEO_SPHEREBODY] = MeshBuilder::GenerateSphere("sphereBODY", Color(1.f, 0.9f, 0.8f), 20, 30, 0.45f);
	meshList[GEO_SPHEREBODY]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHEREBODY]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_SPHEREBODY]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_SPHEREBODY]->material.kShininess = 0.6f;

	meshList[GEO_LEG] = MeshBuilder::GenerateCylinder("leg", Color(1.f, 0.9f, 0.8f), 20, 0.5f);
	meshList[GEO_LEG]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_LEG]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_LEG]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_LEG]->material.kShininess = 0.6f;

	meshList[GEO_TAIL] = MeshBuilder::GenerateCylinder("tail", Color(1.f, 0.5f, 0.f), 20, 0.3f);
	meshList[GEO_TAIL]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_TAIL]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_TAIL]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_TAIL]->material.kShininess = 0.3f;

	meshList[GEO_FEET] = MeshBuilder::GenerateSphere("feet", Color(0.f, 0.f, 0.f), 10, 15);
	meshList[GEO_FEET]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_FEET]->material.kDiffuse.Set(0.6f, 0.6f, 0.6f);
	meshList[GEO_FEET]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_FEET]->material.kShininess = 0.3f;

	meshList[GEO_WINGTOP] = MeshBuilder::GenerateCylinder("wingcylinder", Color(1.f, 0.5f, 0.f), 20);
	meshList[GEO_WINGTOP]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_WINGTOP]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_WINGTOP]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_WINGTOP]->material.kShininess = 0.3f;

	meshList[GEO_WINGPART] = MeshBuilder::GenerateCylinder("wingpartcylinder", Color(1.f, 0.6f, 0.1f), 20, 1, 0.2f);
	meshList[GEO_WINGPART]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_WINGPART]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_WINGPART]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_WINGPART]->material.kShininess = 0.3f;

	meshList[GEO_BASECYLINDER] = MeshBuilder::GenerateCylinder("basecylinder", Color(0.25f, 0.15f, 0.1f), 20);
	meshList[GEO_BASECYLINDER]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BASECYLINDER]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BASECYLINDER]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_BASECYLINDER]->material.kShininess = 0.9f;

	meshList[GEO_BASETORUS] = MeshBuilder::GenerateTorus("basetorus", Color(0.25f, 0.15f, 0.1f), 30, 60, 1.f, 0.3f);
	meshList[GEO_BASETORUS]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BASETORUS]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BASETORUS]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_BASETORUS]->material.kShininess = 0.9f;

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1.f, 1.f, 1.f), 10, 20);

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(0.f, 0.1f, 0.05f));
	meshList[GEO_QUAD]->material.kAmbient.Set(1.f, 1.f, 1.f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(1.f, 1.f, 1.f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_QUAD]->material.kShininess = 0.1f;

	meshList[GEO_EYE] = MeshBuilder::GenerateCylinder("eye", Color(0.4f, 0.8f, 1.f), 20);
	meshList[GEO_EYE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_EYE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYE]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_EYE]->material.kShininess = 0.9f;

	meshList[GEO_EYE_IRIS] = MeshBuilder::GenerateCylinder("iris", Color(0.f, 0.f, 0.f), 20);
	meshList[GEO_EYE_IRIS]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_EYE_IRIS]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYE_IRIS]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_EYE_IRIS]->material.kShininess = 0.9f;

	meshList[GEO_EYE_SHINE] = MeshBuilder::GenerateCylinder("eyeshine", Color(1.f, 1.f, 1.f), 20);
	meshList[GEO_EYE_SHINE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_EYE_SHINE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYE_SHINE]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_EYE_SHINE]->material.kShininess = 0.9f;

	meshList[GEO_EYE_SIDE] = MeshBuilder::GenerateTorus("eyeside", Color(0.f, 0.f, 0.f), 3, 3, 1.f, 1.f);
	meshList[GEO_EYE_SIDE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_EYE_SIDE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYE_SIDE]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_EYE_SIDE]->material.kShininess = 0.9f;

	meshList[GEO_MOUTH] = MeshBuilder::GenerateCylinder("MOUTH", Color(0.5f, 0.1f, 0.1f), 20, 1, 0.5f);
	meshList[GEO_MOUTH]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MOUTH]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_MOUTH]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_MOUTH]->material.kShininess = 0.9f;

	meshList[GEO_DIGIBODY] = MeshBuilder::GenerateCube("Digivicebody", Color(0.7f, 1.f, 1.f));
	meshList[GEO_DIGIBODY]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DIGIBODY]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DIGIBODY]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_DIGIBODY]->material.kShininess = 10.0f;

	meshList[GEO_DIGISIDE] = MeshBuilder::GenerateCylinder("Digiviceside", Color(0.7f, 1.f, 1.f),10,1.f,0.5f);
	meshList[GEO_DIGISIDE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DIGISIDE]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DIGISIDE]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_DIGISIDE]->material.kShininess = 10.0f;

	meshList[GEO_DIGITORUS] = MeshBuilder::GenerateTorus("Digivicetorus", Color(0.6f, 0.9f, 0.9f), 30, 60, 1.f, 0.2f);
	meshList[GEO_DIGITORUS]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_DIGITORUS]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DIGITORUS]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_DIGITORUS]->material.kShininess = 0.9f;

	meshList[GEO_DIGISCREEN1] = MeshBuilder::GenerateCylinder("Digiscreen", Color(0.5f, 0.5f, 0.5f), 15);
	meshList[GEO_DIGISCREEN1]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_DIGISCREEN1]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_DIGISCREEN1]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_DIGISCREEN1]->material.kShininess = 0.9f;

	meshList[GEO_DIGISCREEN2] = MeshBuilder::GenerateCube("Digiscreen2", Color(0.7f, 1.f, 0.7f));
	meshList[GEO_DIGISCREEN2]->material.kAmbient.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_DIGISCREEN2]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_DIGISCREEN2]->material.kSpecular.Set(0.3f, 0.3f, 0.3f);
	meshList[GEO_DIGISCREEN2]->material.kShininess = 0.9f;

	meshList[GEO_DIGIBUTTON] = MeshBuilder::GenerateCylinder("Digivicebutton", Color(0.f, 0.f, 0.7f), 30);
	meshList[GEO_DIGIBUTTON]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_DIGIBUTTON]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DIGIBUTTON]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_DIGIBUTTON]->material.kShininess = 0.9f;

	meshList[GEO_DIGIBUTTONLINE] = MeshBuilder::GenerateTorus("Digivicebuttonline", Color(0.f, 0.f, 0.f), 30, 60, 1.f, 0.1f);
	meshList[GEO_DIGIBUTTONLINE]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_DIGIBUTTONLINE]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DIGIBUTTONLINE]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_DIGIBUTTONLINE]->material.kShininess = 0.9f;

	meshList[GEO_DIGIANTENNA] = MeshBuilder::GenerateCylinder("Digiviceantenna", Color(0.f, 0.f, 0.f), 30, 0.5f);
	meshList[GEO_DIGIANTENNA]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_DIGIANTENNA]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DIGIANTENNA]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_DIGIANTENNA]->material.kShininess = 0.2f;

	meshList[GEO_DIGIEXTRA] = MeshBuilder::GenerateCube("Digivice extra", Color(0.3f, 0.6f, 0.6f));
	meshList[GEO_DIGIEXTRA]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_DIGIEXTRA]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DIGIEXTRA]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_DIGIEXTRA]->material.kShininess = 0.2f;

	meshList[GEO_EGG] = MeshBuilder::GenerateSphere("Egg", Color(0.7f, 0.7f, 0.7f), 10, 20);
	meshList[GEO_EGG]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_EGG]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_EGG]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_EGG]->material.kShininess = 0.2f;

	meshList[GEO_TRANSFORM] = MeshBuilder::GenerateCylinder("Transformation", Color(1.f, 0.f, 0.f), 20);
	meshList[GEO_TRANSFORM]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_TRANSFORM]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TRANSFORM]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_TRANSFORM]->material.kShininess = 0.2f;

	meshList[GEO_AIRSHOT] = MeshBuilder::GenerateSphere("Airshot", Color(0.6f, 0.9f, 0.9f), 10, 20);
	meshList[GEO_AIRSHOT]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_AIRSHOT]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_AIRSHOT]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_AIRSHOT]->material.kShininess = 10.0f;

	meshList[GEO_AIRSHOTTRAIL] = MeshBuilder::GenerateCylinder("Airshot trail", Color(0.6f, 0.9f, 0.9f), 30, 0.f);
	meshList[GEO_AIRSHOTTRAIL]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_AIRSHOTTRAIL]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_AIRSHOTTRAIL]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_AIRSHOTTRAIL]->material.kShininess = 10.0f;

	meshList[GEO_TREE] = MeshBuilder::GenerateCylinder("Tree top", Color(0.1f, 0.2f, 0.1f), 30, 0.f);
	meshList[GEO_TREE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_TREE]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TREE]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_TREE]->material.kShininess = 1.0f;

	meshList[GEO_SKY] = MeshBuilder::GenerateSphere("sky", Color(1.f, 1.f, 0.f), 20, 40,0.5f,true);

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	projectionStack.LoadMatrix(projection);
}

static double debounce = 0.f; // Checking for debounce
static float LSPEED = 10.f; // Speed of Camera

static bool HATCHED = false;
static bool EVOLVING = false;

static float EVOLVE_SIZE = 0.f;

static float WING_SPEED = 60.f;
static float WING_LIMIT = 30;
static float WingFlap = 0.f;
static float BODY_FLOAT = 0.f; // Height increase of Patamon
static float BASE_FLOAT = 0.f; // Base height of Patamon
static bool WING_CHECK = true; // Check direction of wing

static bool FLYING = false;

static float EGG_SHAKE = 0.f; 
static float EGG_WAIT = 0.f;
static bool EGG_CHECK = true;

static float SKY_SIZE = 0.f;
static float SKY_ROTATE = 0.f;

static float AIRSHOTDIST = 0.f; // distance of AIRSHOT
static float PATAMONINFLATION = 1.f; // INFLATION OF PATAMON
static float PATAMONRECOIL = 0.f; // RECOIL OF PATAMON
static bool FIRING = false;

void Asn2::Update(double dt)
{
	camera.Update(dt);
	debounce += dt;

	if (FIRING == true)
	{
		if (PATAMONINFLATION > 1.5 || AIRSHOTDIST > 0.f)
		{
			AIRSHOTDIST += (float)(100 * dt);
			PATAMONINFLATION -= (float)(dt);
			if (AIRSHOTDIST > 50)
			{
				PATAMONINFLATION = 1.f;
				AIRSHOTDIST = 0.f;
				PATAMONRECOIL = 0.f;
				FIRING = false;
			}
			else if (AIRSHOTDIST > 25)
			{
				PATAMONRECOIL -= (float)(10 * dt);
			}
			else
			{
				PATAMONRECOIL += (float)(10 * dt);
			}
		}
		else if (PATAMONINFLATION <= 1.5)
		{
			PATAMONINFLATION += (float)(2 * dt);
		}
	}

	if (EVOLVING == true)
	{
		if (HATCHED == false)
		{
			if (SKY_SIZE < 500)
			{
				SKY_SIZE += (float)(150 * dt);
			}
			EVOLVE_SIZE += (float)(50 * dt);
			if (EVOLVE_SIZE > 70)
			{
				EVOLVING = false;
				HATCHED = true;
			}
		}
		else if (HATCHED == true)
		{
			if (SKY_SIZE > 0)
			{
				SKY_SIZE -= (float)(150 * dt);
			}
			else
			{
				SKY_SIZE = 0.f;
			}
			EVOLVE_SIZE += (float)(50 * dt);
			if (EVOLVE_SIZE > 70)
			{
				EVOLVING = false;
				HATCHED = false;
				FLYING = false;
			}

		}
	}
	else if (EVOLVING == false && EVOLVE_SIZE > 0)
	{
		EVOLVE_SIZE -= (float)(100 * dt);
		if (EVOLVE_SIZE < 0)
		{
			EVOLVE_SIZE = 0.f;
		}
	}

	if (EGG_WAIT > 1.f)
	{
		if (EGG_CHECK == true)
		{
			EGG_SHAKE += (float)(100 * dt);
			if (EGG_SHAKE > 10)
				EGG_CHECK = false;
		}
		else if (EGG_CHECK == false)
		{
			EGG_SHAKE -= (float)(100 * dt);
			if (EGG_SHAKE < -10)
			{
				EGG_CHECK = true;
				EGG_WAIT = 0.f;
			}
		}
	}
	else
		EGG_WAIT += (float)dt;


	SKY_ROTATE += (float)(30 * dt); // rotation of sky thingy

	if (FLYING == true)
	{
		if (WingFlap < WING_LIMIT && WING_CHECK == true)
		{
			if (BASE_FLOAT < 6)
				BASE_FLOAT += (float)(10*dt);
			WingFlap += (float)(WING_SPEED * dt);
			BODY_FLOAT -= (float)(WING_SPEED / 8 * dt);
			if (WingFlap >= WING_LIMIT)
				WING_CHECK = false;
		}
		else if (WingFlap > -5 && WING_CHECK == false)
		{
			if (BASE_FLOAT < 6)
				BASE_FLOAT += (float)(10*dt);
			WingFlap -= (float)(WING_SPEED * dt);
			BODY_FLOAT += (float)(WING_SPEED / 8 * dt);
			if (WingFlap <= -5)
				WING_CHECK = true;
		}
	}
	else
	{
		if (BASE_FLOAT > 0)
			BASE_FLOAT -= (float)(10*dt);
		BODY_FLOAT = 0.f;
		WingFlap = 0.f;
	}
		

	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode


	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED *dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED *dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED *dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED *dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED *dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED *dt);

	if (Application::IsKeyPressed('U'))
	{
		if (LightSwitch == true && debounce > 0.2)
		{
			LightSwitch = false;
			debounce = 0.f;
		}
		else if (debounce > 0.2)
		{
			LightSwitch = true;
			debounce = 0.f;
		}
	}

	//----------------------------------[ANIMATIONS]------------------------------------//

	if (Application::IsKeyPressed('F')) // flying
	{
		if (FLYING == true && debounce > 0.2 && HATCHED == true)
		{
			FLYING = false;
			debounce = 0.f;
		}
		else if (debounce > 0.2 && HATCHED == true)
		{
			FLYING = true;
			debounce = 0.f;
		}
	}

	if (Application::IsKeyPressed(' ')) // evolve
	{
		if (EVOLVING == false && EVOLVE_SIZE == 0.f)
		{
			EVOLVING = true;
		}
	}

	if (Application::IsKeyPressed('E')) // shooting
	{
		if (FIRING == false)
		{
			FIRING = true;
		}
	}

}

void Asn2::RenderMesh(Mesh*mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();

		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load materials
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	mesh->Render();
}

void Asn2::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Set view matrix using camera settings
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);

	modelStack.LoadIdentity();

	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix(); // BASEPLATE
		modelStack.Scale(1000, 1000, 1000);
		RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix(); // LIGHT
		modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
		RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	if (SKY_SIZE > 1) // COSMETIC STUFF
	{
		modelStack.PushMatrix(); // THE CIRCLE THINGY IN THE SKY
			modelStack.Rotate(SKY_ROTATE, 0, 1, 0);
			modelStack.Translate(0, -1, 0);
			modelStack.Scale(SKY_SIZE, SKY_SIZE, SKY_SIZE);
			modelStack.Rotate(180, 0, 0, 1);
			RenderMesh(meshList[GEO_SKY], false);
		modelStack.PopMatrix();
	}
	for (int z = 0; z < 2; ++z)
	{
		for (int i = 0; i < 4; ++i) // BACKGROUND TREES
		{
			modelStack.PushMatrix();
			if (z == 0)
				modelStack.Scale(1, 1, 1);
			else
				modelStack.Scale(10, 10, 10);
			if (i == 0)
				modelStack.Translate(-30, 0, -30);
			else if (i == 1)
				modelStack.Translate(30, 0, 30);
			else if (i == 2)
				modelStack.Translate(30, 0, -30);
			else
				modelStack.Translate(-30, 0, 30);
			modelStack.Translate(0, 30, 0);
			modelStack.PushMatrix();
			modelStack.Scale(10, 30, 10);
			RenderMesh(meshList[GEO_TREE], LightSwitch);
			modelStack.PopMatrix();
			modelStack.Translate(0, -22, 0);
			modelStack.Scale(3, 15, 3);
			RenderMesh(meshList[GEO_BASECYLINDER], LightSwitch);
			modelStack.PopMatrix();
		}
	}

	if (HATCHED == false)
	{
		modelStack.PushMatrix(); // EGG
			modelStack.Rotate(EGG_SHAKE, 1, 0, 0);
			modelStack.Translate(1.5, 4, 0);
			modelStack.Scale(3, 4.5, 3);
			RenderMesh(meshList[GEO_EGG], LightSwitch);
		modelStack.PopMatrix();


		modelStack.PushMatrix(); // NEST
			modelStack.Translate(2, 0, 0);

			modelStack.PushMatrix();
				modelStack.Scale(10, 1, 10);
				RenderMesh(meshList[GEO_BASECYLINDER], LightSwitch);
			modelStack.PopMatrix();

			modelStack.Scale(10, 10, 10);
			RenderMesh(meshList[GEO_BASETORUS], LightSwitch);
		modelStack.PopMatrix();
	}

	//----------------------------------[DIGIVICE]------------------------------------//

	modelStack.PushMatrix(); // DIGIVICE

		modelStack.Translate(0, 30, 0);
		modelStack.Rotate(-90, 0, 1, 0);

		if (EVOLVE_SIZE > 0)
		{
			modelStack.PushMatrix(); //  SIZE OF EVOLUTION BEAM
				modelStack.Scale(20, (float)EVOLVE_SIZE*10 + 0.1f, 20);
				RenderMesh(meshList[GEO_TRANSFORM], LightSwitch);
			modelStack.PopMatrix(); // END OF THE BEAM
		}

		modelStack.PushMatrix(); // Body of Digivice
			modelStack.Scale(6, 4, 2);
			RenderMesh(meshList[GEO_DIGIBODY], LightSwitch);
		modelStack.PopMatrix();
	
		for (int i = 0; i < 2; ++i)
		{
			modelStack.PushMatrix(); // TOP SIDE AND BOTTOM SIDE
				if (i == 1)
					modelStack.Rotate(180, 1, 0, 0);
				modelStack.Translate(0, 2, 0);
				modelStack.Rotate(180, 0, 1, 0);
				modelStack.Rotate(-90, 1, 0, 0);
				modelStack.Scale(3, 2, 2);
				RenderMesh(meshList[GEO_DIGISIDE], LightSwitch);
				modelStack.Translate(0.3f, 0, 0.7f);
				modelStack.Scale(0.2f, 1.2f, 0.7f);
				modelStack.Rotate(90, 0, 0, 1);
				RenderMesh(meshList[GEO_DIGIEXTRA], LightSwitch);
				modelStack.Translate(0, 3.f,0);
				RenderMesh(meshList[GEO_DIGIEXTRA], LightSwitch);
			modelStack.PopMatrix();
		}

		for (int i = 0; i < 2; ++i)
		{
			modelStack.PushMatrix(); // LEFT AND RIGHT SIDE
				if (i == 1)
					modelStack.Translate(-2.9f, 0, 0);
				else{
					modelStack.Translate(2.9f, 0, 0);
					modelStack.Rotate(180, 0, 0, 1);
				}
				modelStack.Rotate(90, 0, 0, 1);
				modelStack.Rotate(180, 0, 0, 1);
				modelStack.Rotate(90, 1, 0, 0);
				modelStack.Scale(2.5f, 1.9f, 2);
				RenderMesh(meshList[GEO_DIGISIDE], LightSwitch);
				modelStack.Translate(0.3f, 0, 0.5f);
				if (i == 0)
				{
					modelStack.Translate(0, 0, 0.1f);
					modelStack.Scale(0.2f, 1.2f, 0.7f);
					modelStack.Rotate(90, 0, 0, 1);
					RenderMesh(meshList[GEO_DIGIEXTRA], LightSwitch);
					modelStack.Translate(0, 3.f, 0);
					RenderMesh(meshList[GEO_DIGIEXTRA], LightSwitch);
				}
				else if (i == 1)
				{
					modelStack.Translate(0, 0, 0.2f);
					modelStack.Scale(0.3f, 1.2f, 0.7f);
					modelStack.Rotate(90, 0, 0, 1);
					modelStack.Translate(0, 1.f, 0);
					RenderMesh(meshList[GEO_DIGIEXTRA], LightSwitch);
				}
			modelStack.PopMatrix();
		}

		modelStack.PushMatrix(); // CIRCLE OF DIGIVICE
			modelStack.Translate(0, 0, 1);
			modelStack.Rotate(90, 1, 0, 0);
			modelStack.Scale(2.5, 1.5, 2.5);
			RenderMesh(meshList[GEO_DIGITORUS], LightSwitch);
		modelStack.PopMatrix();

		modelStack.PushMatrix(); // SCREEN OF DIGIVICE
			modelStack.Translate(0, 0, 1);
			modelStack.Rotate(90, 1, 0, 0);
			modelStack.Scale(2.5, 0.5, 2.5);
			modelStack.PushMatrix();
				modelStack.Translate(0, 0.1f, 0);
				modelStack.Scale(1.1f, 1, 1.1f);
				RenderMesh(meshList[GEO_DIGISCREEN2], LightSwitch); // GREEN PART
			modelStack.PopMatrix();
			RenderMesh(meshList[GEO_DIGISCREEN1], LightSwitch); // BLACK PART
		modelStack.PopMatrix();

		modelStack.PushMatrix(); // DIGIVICE BUTTONS
			modelStack.Translate(-3.3f, 0, 1.2f); // LARGER LEFT BUTTON
			modelStack.Rotate(90, 1, 0, 0);
			modelStack.Scale(0.7f, 0.5f, 0.7f);
			RenderMesh(meshList[GEO_DIGIBUTTON], LightSwitch);

			modelStack.PushMatrix(); // LINES
				modelStack.Translate(0, -0.4f, 0);
				RenderMesh(meshList[GEO_DIGIBUTTONLINE], LightSwitch);
			modelStack.PopMatrix();

			modelStack.PushMatrix();
				modelStack.Translate(0, 0.5, 0);
				modelStack.Scale(0.5, 2, 0.5);
				RenderMesh(meshList[GEO_DIGIBUTTONLINE], LightSwitch);
			modelStack.PopMatrix();

		modelStack.PopMatrix();
		for (int i = 0; i < 2; ++i)
		{
			modelStack.PushMatrix();  // SMALLER RIGHT BUTTONS
				if (i == 0)
					modelStack.Translate(3.3f, 0.8f, 1.2f);
				else
					modelStack.Translate(3.3f, -0.8f, 1.2f);
				modelStack.Rotate(90, 1, 0, 0);
				modelStack.Scale(0.7f, 0.5f, 0.5f);
				RenderMesh(meshList[GEO_DIGIBUTTON], LightSwitch);

				modelStack.PushMatrix();
					modelStack.Translate(0.f, -0.4f, 0.f);
					RenderMesh(meshList[GEO_DIGIBUTTONLINE], LightSwitch); // LINES
				modelStack.PopMatrix();

				modelStack.PushMatrix();
					modelStack.Translate(0, 0.5, 0);
					modelStack.Scale(0.5, 2, 0.5);
					RenderMesh(meshList[GEO_DIGIBUTTONLINE], LightSwitch);
				modelStack.PopMatrix();

			modelStack.PopMatrix();
		}

		modelStack.PushMatrix(); // DIGIVICE ANTENNA
			modelStack.Translate(-3.5, 3, 0);
			modelStack.Rotate(45, 0, 0, 1);
			modelStack.Scale(0.7f, 1.5f, 0.7f);
			RenderMesh(meshList[GEO_DIGIANTENNA], LightSwitch);
		modelStack.PopMatrix();

	modelStack.PopMatrix(); // end of digivice

	//----------------------------------[END DIGIVICE]------------------------------------//

	//----------------------------------[PATAMON]------------------------------------//

	if (HATCHED == true) // Only renders if it is hatched
	{
		modelStack.PushMatrix(); // 1  // PATAMON
			modelStack.Translate(0 + PATAMONRECOIL, 0.5 + BODY_FLOAT + BASE_FLOAT, 0);
			modelStack.Rotate(WingFlap/4, 0, 0, 1);
			if (AIRSHOTDIST > 0.f)
			{
				modelStack.PushMatrix(); // AIRSHOT
					modelStack.Translate(-6 - AIRSHOTDIST * 2, 4, 0);

					modelStack.PushMatrix();
						modelStack.Translate(4, 0, 0);
						modelStack.Rotate(-90, 0, 0, 1);
						modelStack.Scale(2, 5, 2);
						RenderMesh(meshList[GEO_AIRSHOTTRAIL], LightSwitch);
					modelStack.PopMatrix();

					modelStack.Scale(3, 3, 3);
					RenderMesh(meshList[GEO_AIRSHOT], LightSwitch);
				modelStack.PopMatrix();
			}

			modelStack.PushMatrix(); // mouth
				modelStack.Translate(-6, 4, 0);
				modelStack.Rotate(90, 0, 1, 0);
				modelStack.Rotate(90, 1, 0, 0);
				modelStack.Scale(0.5f * PATAMONINFLATION * 2.f, 0.1f, 0.5f * PATAMONINFLATION * 2.f);
				RenderMesh(meshList[GEO_MOUTH], true);
			modelStack.PopMatrix();

			for (int i = 0; i < 2; ++i) // EYES
			{
				modelStack.PushMatrix(); // 9
					if (i == 0)
						modelStack.Translate(-6, 6, 2);
					else
						modelStack.Translate(-6, 6, -2);

					modelStack.Rotate(90, 0, 0, 1);
					modelStack.Scale(1, 0.1f, 1);
					modelStack.PushMatrix();
						modelStack.Translate(0, -0.5, 1);
						modelStack.Scale(0.2f, 1, 0.2f);
						RenderMesh(meshList[GEO_EYE_SIDE], LightSwitch);

						modelStack.PushMatrix();
							modelStack.Translate(0, 0, -10);
							modelStack.Rotate(180, 1, 0, 0);
							RenderMesh(meshList[GEO_EYE_SIDE], LightSwitch); // TRIANGLES
						modelStack.PopMatrix();

					modelStack.PopMatrix();
					RenderMesh(meshList[GEO_EYE], LightSwitch); // BLUE

					modelStack.PushMatrix();
						modelStack.Scale(1.1f, 0.1f, 1.1f);
						modelStack.Translate(0, -0.1f, 0);
						RenderMesh(meshList[GEO_EYE_IRIS], LightSwitch);
					modelStack.PopMatrix();

					modelStack.PushMatrix();
						modelStack.Translate(0, 0.2f, 0);
						modelStack.Scale(0.6f, 1.5f, 0.6f);
						RenderMesh(meshList[GEO_EYE_IRIS], LightSwitch); // BLACK PART
					modelStack.PopMatrix();

					modelStack.PushMatrix();
						modelStack.Translate(0.3f, 0.6f, -0.5f);
						modelStack.Scale(0.4f, 1, 0.4f);
						RenderMesh(meshList[GEO_EYE_SHINE], LightSwitch);
					modelStack.PopMatrix();

					modelStack.PushMatrix();
						modelStack.Translate(-0.5f, 0.6f, 0.4f);
						modelStack.Scale(0.3f, 1, 0.3f);
						RenderMesh(meshList[GEO_EYE_SHINE], LightSwitch); // WHITE PARTS
					modelStack.PopMatrix();

				modelStack.PopMatrix(); // 9
			}

			modelStack.PushMatrix(); // 2 TORSO
				modelStack.PushMatrix();
					if (FIRING == true)
					{
						modelStack.Translate(PATAMONINFLATION / 5, 0, 0);
						modelStack.Scale(PATAMONINFLATION, PATAMONINFLATION, PATAMONINFLATION);
					}

					modelStack.PushMatrix(); // 6	// TAIL
						modelStack.Translate(11, 7, 0);
						modelStack.Rotate(-45, 0, 0, 1);
						modelStack.Scale(0.5, 2, 0.5);
						RenderMesh(meshList[GEO_TAIL], LightSwitch);
					modelStack.PopMatrix(); // 6

				modelStack.PopMatrix();
				modelStack.Scale(6, 5, 5);
				modelStack.Translate(0, 1, 0);
				RenderMesh(meshList[GEO_SPHEREBODY], LightSwitch);

				modelStack.PushMatrix(); // 3
					modelStack.Rotate(180, 0, 0, 1);
					RenderMesh(meshList[GEO_SPHERE], LightSwitch);
				modelStack.PopMatrix(); // 3

				if (FIRING == true)
				{
					modelStack.Translate(PATAMONINFLATION / 5, 0, 0);
					modelStack.Scale(PATAMONINFLATION, PATAMONINFLATION, PATAMONINFLATION);
				}
				modelStack.Scale(1.2f, 0.95f, 0.95f);
				modelStack.Translate(0.5, 0, 0);
				RenderMesh(meshList[GEO_SPHEREBODY], LightSwitch);

				modelStack.PushMatrix(); // 4
					modelStack.Rotate(180, 0, 0, 1);
					RenderMesh(meshList[GEO_SPHERE], LightSwitch);
				modelStack.PopMatrix(); // 4

			modelStack.PopMatrix(); // 2


			for (int i = 0; i < 4; ++i) // LEGS
			{
				modelStack.PushMatrix(); // 5
					if (i == 0)
						modelStack.Translate(7, 1 - (PATAMONINFLATION - 1)*5, 2.5);
					else if (i == 1)
						modelStack.Translate(7, 1 - (PATAMONINFLATION - 1)*5, -2.5);
					else if (i == 2)
						modelStack.Translate(-2, 1, -2.5);
					else if (i == 3)
						modelStack.Translate(-2, 1, 2.5);
					modelStack.Rotate(-PATAMONRECOIL*30, 0, 0, 1);

					modelStack.PushMatrix(); // a
						modelStack.Translate(-0.5f, -1.2f, 0.5f);
						modelStack.Scale(0.5, 0.5, 0.5);
						RenderMesh(meshList[GEO_FEET], LightSwitch);
						modelStack.Translate(0, 0, -1.7f);
						RenderMesh(meshList[GEO_FEET], LightSwitch);
						modelStack.Translate(-0.7f, 0, 1);
						RenderMesh(meshList[GEO_FEET], LightSwitch);
					modelStack.PopMatrix(); // a

					modelStack.Rotate(180, 0, 0, 1);
					modelStack.Scale(1, 3, 1);
					RenderMesh(meshList[GEO_LEG], LightSwitch);
				modelStack.PopMatrix(); // 5
			}


			for (int i = 0; i < 2; ++i) // WINGS
			{
				modelStack.PushMatrix(); // 7
					modelStack.Scale(1, 1.2f, 1);
					if (i == 0)
					{
						modelStack.Translate(-1, 8, 2);
						modelStack.Rotate(90, 0, 1, 0); // ROTATE ENTIRE WING
						modelStack.Rotate(-WingFlap + 30, 0, 0, 1);
					}
					else
					{
						modelStack.Translate(-1, 8, -2);
						modelStack.Rotate(90, 0, 1, 0); // ROTATE ENTIRE WING
						modelStack.Rotate(WingFlap - 30, 0, 0, 1);
					}

					modelStack.Translate(0, 3, 0);

					modelStack.PushMatrix();
						modelStack.Scale(0.5, 8, 0.5);
						RenderMesh(meshList[GEO_WINGTOP], LightSwitch);
					modelStack.PopMatrix();

					modelStack.PushMatrix();
						modelStack.Rotate(45, 1, 0, 0);
						modelStack.Translate(0, 5, -2.8f);
						modelStack.Scale(0.5, 5, 0.5);
						RenderMesh(meshList[GEO_WINGTOP], LightSwitch);
					modelStack.PopMatrix();

					modelStack.PushMatrix();
						modelStack.Translate(0, 2.5, 2.5);
						modelStack.Rotate(120, 1, 0, 0);
						modelStack.Scale(0.5, 5, 0.5);
						RenderMesh(meshList[GEO_WINGTOP], LightSwitch);
					modelStack.PopMatrix();

					modelStack.PushMatrix();
						modelStack.Translate(0, 4, 0);
						modelStack.Rotate(-50, 1, 0, 0);
						modelStack.Rotate(-90, 0, 1, 0);
						modelStack.Rotate(90, 1, 0, 0);
						modelStack.Scale(4, 0.3f, 4);
						RenderMesh(meshList[GEO_WINGPART], LightSwitch);
					modelStack.PopMatrix();

					modelStack.PushMatrix();
						modelStack.Translate(0, 3.5, 0);
						modelStack.Rotate(20, 1, 0, 0);
						modelStack.Rotate(-90, 0, 1, 0);
						modelStack.Rotate(90, 1, 0, 0);
						modelStack.Scale(4, 0.3f, 5);
						RenderMesh(meshList[GEO_WINGPART], LightSwitch);
					modelStack.PopMatrix();

				modelStack.PopMatrix(); // 7
			}
		modelStack.PopMatrix(); // 1
	}
	//----------------------------------[END OF DIGIVICE]------------------------------------//
	

}



void Asn2::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}