#include "Assignment3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "LoadTGA.h"
#include "Utility.h"

#include "Enemy.h"
#include "CountDown.h"
#include "Rock.h"
#include "Flag.h"
#include "Astronaut.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Ship.h"

#include <stdlib.h>
#include <sstream>

#include "Music.h"

extern GLFWwindow* m_window;

using std::cout;
using std::endl;


vector<Rock> Rocks;
vector<Turret> Turrets;
Weapon pistol(20, 30, 100, 5, false);
Flag f(Vector3(0, 0.75f, 0), Vector3(1, 1, 1));
Astronaut a(Vector3(5, -1, 0));
Ship ship(Vector3(0,0,-50),Vector3(5,5,5));
Weapon SniperRifle(150,10,100,100,true);

Assignment3::Assignment3()
{
}

Assignment3::~Assignment3()
{
}

float Assignment3::getMagnitude(const Vector3 object, const Vector3 target)
{
	Vector3 a;
	a.x = object.x - target.x;
	a.y = object.y - target.y;
	a.z = object.z - target.z;
	return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

void Assignment3::Init()
{
	gameState = GS_MAIN;
	CameraMouseUpdate = true;
	player.WeaponState = 3;
	pistol.init(&camera);
	ship.init(&camera);
	SniperRifle.init(&camera);

	//srand
	KillMessage.TimeCountDown(0.3);
	srand(time_t(NULL));
	for (float i = 0; i < 3; ++i)
	{
		Aliens.push_back(Enemy(Vector3(i*2, 0, i*2), Vector3(0, 0, 0), Vector3(0.5, 1, 0.5)));
	}
	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.1f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);


	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

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
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");


	glUseProgram(m_programID);

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0.f, 10.f, 20.f);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.1f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.0f, 1.0f, 0.0f);

	light[1].type = Light::LIGHT_SPOT;
	
	light[1].color.Set(1, 1, 1);
	light[1].power = 0.5;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(30));
	light[1].cosInner = cos(Math::DegreeToRadian(10));
	light[1].exponent = 3.f;
	light[1].position.Set(camera.position.x, camera.position.y, camera.position.z);
	light[1].spotDirection.Set(camera.target.x, camera.target.y, camera.target.z);


	// Pass information
	glUniform1i(m_parameters[U_NUMLIGHTS], 2);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);


	//Initialize camera settings
	camera.Init(Vector3(0, 0, 30), Vector3(10,0,0), Vector3(0, 1, 0),&Rocks);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 0), 10, 20);

	meshList[GEO_BULLET] = MeshBuilder::GenerateSphere("bullet", Color(1, 1, 1), 3, 3);

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//moon.tga");

	meshList[GEO_ROCK] = MeshBuilder::GenerateOBJ("Boulder", "OBJ//Rock.obj");
	meshList[GEO_ROCK]->textureID = LoadTGA("Image//boulder.tga");

	meshList[GEO_CRATER] = MeshBuilder::GenerateOBJ("crater", "OBJ//crater.obj");
	meshList[GEO_CRATER]->textureID = LoadTGA("Image//crater.tga");

	meshList[GEO_ALIENHEAD] = MeshBuilder::GenerateOBJ("alienhead", "OBJ//alienhead.obj");
	meshList[GEO_ALIENHEAD]->textureID = LoadTGA("Image//ALIENHEAD.tga");

	meshList[GEO_ALIENPART] = MeshBuilder::GenerateOBJ("alienpart", "OBJ//alienpart.obj");
	meshList[GEO_ALIENPART]->textureID = LoadTGA("Image//ALIENBODY.tga");

	meshList[GEO_ALIENBODY] = MeshBuilder::GenerateOBJ("alienbody", "OBJ//alienbody.obj");
	meshList[GEO_ALIENBODY]->textureID = LoadTGA("Image//ALIENBODY.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//grisaiaCustom.tga");

	meshList[GEO_FLAGPOLE] = MeshBuilder::GenerateOBJ("Pole", "OBJ//flagpole.obj");
	meshList[GEO_FLAGPOLE]->textureID = LoadTGA("Image//flagpoleUV.tga");

	meshList[GEO_ENEMYFLAG] = MeshBuilder::GenerateOBJ("OurFlag", "OBJ//flag.obj");
	meshList[GEO_ENEMYFLAG]->textureID = LoadTGA("Image//enemyFlag.tga");

	meshList[GEO_ALLYFLAG] = MeshBuilder::GenerateOBJ("enemyFlag", "OBJ//flag.obj");
	meshList[GEO_ALLYFLAG]->textureID = LoadTGA("Image//OurFlag.tga");

	meshList[GEO_UNCAPTURED] = MeshBuilder::GenerateTorus("UncapturedZone", Color(1, 0, 0), 18, 18, 1.f, 0.05f);
	meshList[GEO_CAPTURED] = MeshBuilder::GenerateTorus("CapturedZone", Color(0, 0, 1), 18, 18, 1.f, 0.05f);

	meshList[GEO_ALLYFLAG] = MeshBuilder::GenerateOBJ("enemyFlag", "OBJ//flag.obj");
	meshList[GEO_ALLYFLAG]->textureID = LoadTGA("Image//OurFlag.tga");

	meshList[GEO_PICKAXE] = MeshBuilder::GenerateOBJ("pickaxe", "OBJ//pickaxe.obj");
	meshList[GEO_PICKAXE]->textureID = LoadTGA("Image//pickaxeUV.tga");

	meshList[GEO_GUN] = MeshBuilder::GenerateOBJ("gun", "OBJ//gun.obj");
	meshList[GEO_GUN]->textureID = LoadTGA("Image//gunUV.tga");

	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateText("crosshair", 16, 16);
	meshList[GEO_CROSSHAIR]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_HITORNOT] = MeshBuilder::GenerateQuad("hitornot", Color(1, 1, 1));
	meshList[GEO_HITORNOT]->textureID = LoadTGA("Image//hitOrNot.tga");

	meshList[GEO_ASTRONAUT] = MeshBuilder::GenerateOBJ("Astronaut", "OBJ//astronaut.obj");
	meshList[GEO_ASTRONAUT]->textureID = LoadTGA("Image//astronautUV.tga");

	meshList[GEO_TURRETHEAD] = MeshBuilder::GenerateOBJ("turrettop", "OBJ//TurretHead.obj");
	meshList[GEO_TURRETHEAD]->textureID = LoadTGA("Image//turrettop.tga");

	meshList[GEO_TURRETBASE] = MeshBuilder::GenerateOBJ("TurretBase", "OBJ//TurretBase.obj");
	meshList[GEO_TURRETBASE]->textureID = LoadTGA("Image//turretbottom.tga");

	meshList[GEO_PLAYERHP] = MeshBuilder::GenerateQuad("PlayerHP", Color(1, 0, 0));

	meshList[GEO_UI] = MeshBuilder::GenerateQuad("UI Screen", Color(1,1,1));
	meshList[GEO_UI]->textureID = LoadTGA("Image//UI_Frame.tga");

	meshList[GEO_INFO] = MeshBuilder::GenerateQuad("Info", Color(1, 1, 1));
	meshList[GEO_INFO]->textureID = LoadTGA("Image//instructions.tga");

	meshList[GEO_HEALTH] = MeshBuilder::GenerateQuad("Health", Color(1, 0, 1));

	meshList[GEO_SPACESHIP] = MeshBuilder::GenerateOBJ("Spaceship", "OBJ//SpaceObject.obj");
	meshList[GEO_SPACESHIP]->textureID = LoadTGA("Image//SpaceObjectUV.tga");

	meshList[GEO_SNIPERRIFLE] = MeshBuilder::GenerateOBJ("/SniperRifle", "OBJ//SniperRifle.obj");
	meshList[GEO_SNIPERRIFLE]->textureID = LoadTGA("Image///SniperRifle.tga");

	meshList[GEO_FADE] = MeshBuilder::GenerateQuad("Fade", Color(0, 0, 0));

	Mtx44 projection;
	projection.SetToPerspective(70.0f, 4.0f / 3.0f, 0.1f, 5000.0f);
	projectionStack.LoadMatrix(projection);

}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

static float LSPEED = 10.f; // LIGHT SPEED

static float skyBoxRotate = 0.f; // rotation of skybox

static std::stringstream framerate;
static std::stringstream resources;

void Assignment3::Update(double dt)
{
	if (gameState == GS_MAIN)
	{
		camera.OnControls = true;
	}

	else if (gameState == GS_ASTRONAUT_INTERACTION)
	{
		camera.OnControls = false;
		if (Application::IsKeyPressed('Y'))
		{
			a.UpgradeWeapon(pistol, player);
			gameState = GS_MAIN;
		}
		if (Application::IsKeyPressed('N'))
		{
			gameState = GS_MAIN;
		}
	}

	//************************************Will change this function to a pause function//
	//countdown for camera lock
	countdownCameraLock.TimeCountDown(dt);
	infoscreen.TimeCountDown(dt);

	//mouse rotation of camera
	if (Application::IsKeyPressed(0x50) && countdownCameraLock.GetTimeNow() <= 0)
	{
		if (CameraMouseUpdate == false){ CameraMouseUpdate = true; }
		else{ CameraMouseUpdate = false; }
		countdownCameraLock.resetTime();
	}
	if (CameraMouseUpdate == true)
	{
		camera.Update(dt);
		framerate.str("");
		resources.str("");
		////*********************************************////
		pistol.update(dt);
		debounce.TimeCountDown(dt);
		if (Application::IsKeyPressed(0x31) && debounce.GetTimeNow() < 0)
		{
			debounce.resetTime();
			player.WeaponState = 2;
		}
		if (Application::IsKeyPressed(0x32) && debounce.GetTimeNow() < 0)
		{
			debounce.resetTime();
			player.WeaponState = 1;
		}
		if (Application::IsKeyPressed(0x33) && debounce.GetTimeNow() < 0)
		{
			debounce.resetTime();
			player.WeaponState = 3;
		}
		if (Application::IsKeyPressed('6') && debounce.GetTimeNow() < 0)
		{
			debounce.resetTime();
			player.WeaponState = 6;
		}
		// updating 2nd light
		light[1].position.Set(camera.position.x + camera.target.x / 15,
			camera.position.y + camera.target.y / 15,
			camera.position.z + camera.target.z / 15);
		light[1].spotDirection.Set(-(camera.target.x - camera.position.x), -(camera.target.y - camera.position.y), -(camera.target.z - camera.position.z));

		//first light
		light[0].position.Set(0.f, 5.f, 20.f);
		//Alien Spawn
		if ((countdownAlienSpawn.TimeCountDown(dt) <= 0) && (Aliens.size()) < 20 && (f.flagIsBlue == true))
		{
			countdownAlienSpawn.resetTime();
			float spwanAlienz = (rand() % 100 - 50.f);
			short s = rand() % 3;
			std::cout << s << std::endl;
			if (s == 0)
			{
				Enemy newAlien(Vector3(55.f, 0.f, spwanAlienz), Vector3(camera.position.x, -1.f, camera.position.z), Vector3(0.5, 1, 0.5), 100, 5, 10, 10);
				Aliens.push_back(newAlien);
			}
			else if (s == 1)
			{
				Enemy newAlien(Vector3(55.f, 0.f, spwanAlienz), Vector3(camera.position.x, -1.f, camera.position.z), Vector3(0.5, 1, 0.5), 200, 5, 5, 10, 2.0f);
				Aliens.push_back(newAlien);
			}
			else
			{
				Enemy newAlien(Vector3(55.f, 0.f, spwanAlienz), Vector3(camera.position.x, -1.f, camera.position.z), Vector3(0.5, 1, 0.5), 40, 5, 17, 10, 0.7f);
				Aliens.push_back(newAlien);
			}
		}
		KillMessage.TimeCountDown(dt);
		//Alien update
		for (vector<Enemy>::iterator it = Aliens.begin(); it != Aliens.end();)
		{
			(*it).update(camera, dt, &player);
			if ((*it).isDead())
			{
				Alienresources = rand() % 15 + 5;
				KillMessage.resetTime();
				player.ObtainResources(Alienresources);
				it = Aliens.erase(it);
			}
			else
			{
				++it;
			}
		}

		//Rocks spawn
		if (countdownRock.TimeCountDown(dt) <= 0 && Rocks.size() < 10)
		{
			randomx = rand() % 100 - 50.f;
			randomz = rand() % 100 - 50.f;

			if (getMagnitude(Vector3(randomx, -1, randomz), Vector3(camera.position.x, -1, camera.position.z)) >= 20.0f)//spwan 20 units away from the player
			{
				countdownRock.resetTime();
				Rock newRock(Vector3(randomx, -1.f, randomz), rand() % 4 + 1.f);
				Rocks.push_back(newRock);
			}
		}
		//Turrets Aim and Shoot
		for (size_t i = 0; i < Turrets.size(); i++)
		{
			if (Aliens.empty() == true){ Turrets[i].bulletPos = (0, -10, 0); }
			short s = 0;
			if (Aliens.empty() == false)
			{
				while (s < Aliens.size())
				{
					if (getMagnitude(Turrets[i].GetPosition(), Aliens[s].position) <= 15.f)
					{
						Turrets[i].LookAtEnemy(Aliens[s]);
						Turrets[i].TargetEnemy(Aliens[s].position);
						Turrets[i].ShootAtEnemy(dt);
						if (Turrets[i].shooting == true)
						{
							if (getMagnitude(Turrets[i].bulletPos, Turrets[i].Target) <= 1.0f && Turrets[i].hit == false)
							{
								Turrets[i].hit = true;
								Turrets[i].bulletPos = (0, -10, 0);
								Aliens[s].EnemyTakeDmg(Turrets[i].GetDamage());
							}
						}
						break;
					}
					else if (Turrets[i].shooting == true)
					{
						Turrets[i].bulletPos = Turrets[i].GetPosition();
						Turrets[i].bulletPos.y = -0.5f;
					}
					s++;
				}
			}
		}
		//Rock mining
		player.WhileMining(dt);
		//Timers
		countdownMining.TimeCountDown(dt);
		countdownTurretSpawn.TimeCountDown(dt);
		countdownPistol.TimeCountDown(dt);
		CountdownSniperRifle.TimeCountDown(dt);
		if (Application::IsKeyPressed(VK_LBUTTON)) //check for keypress and weapon holding
		{

			if (player.WeaponState == 1 && (Rocks.empty() == 0) && (countdownMining.GetTimeNow() <= 0))
			{
				vector<Rock>::iterator i = Rocks.begin();
				while (i != Rocks.end())
				{
					if ((getMagnitude(Vector3((*i).position.x, -1, (*i).position.z), Vector3(camera.position.x, camera.position.y - 1, camera.position.z)) - (*i).Size * 2.f) < 0
						&& player.getAngle(camera.view, Vector3((*i).position.x, -1, (*i).position.z) - camera.position) < 45.f)
					{
						if (player.isMining == false)
						{
							player.isMining = true;
							resourceOfRock = (*i).GetResources();
							player.ObtainResources(resourceOfRock);
							(*i).ReduceSize();
						}
						if ((*i).Size <= 0)
						{
							Rocks.erase(i);
						}
						countdownMining.resetTime();
						break;
					}
					else{ i++; }
				}
			}
			if (player.WeaponState == 2 && countdownPistol.GetTimeNow() <= 0)
			{
				pistol.Fire(&Aliens);
				countdownPistol.resetTime();
			}
			if (player.WeaponState == 3 && CountdownSniperRifle.GetTimeNow() <=0)
			{
				SniperRifle.FireSR(&Aliens);
				CountdownSniperRifle.resetTime();
			}
			else if (player.WeaponState == 6 && countdownTurretSpawn.GetTimeNow() <= 0 /*&& player.getResources() >= 50*/)
			{
				/////////////////////Add requirements for resources///////////////
				float a = 1; //used to mutiply camera view to get intersection with 0
				if (camera.target.y <= 0)
				{
					while (TurretPos.y >= -1)
					{
						TurretPos = camera.view*a;
						a += 0.1;
					}
					player.ObtainResources(-50);
					Turret newTurret(100, 50, Vector3(TurretPos.x + camera.position.x, 0, TurretPos.z + camera.position.z));
					Turrets.push_back(newTurret);
					countdownTurretSpawn.resetTime();
					TurretPos = (0.f, 0.f, 0.f);//reset the value of the variable
				}
			}
		}
		if (Application::IsKeyPressed(VK_RBUTTON) && isZoom == false && rightClick.TimeCountDown(dt) < 0)
		{
			if (player.WeaponState == 2)
			{
				Mtx44 projection;
				projection.SetToPerspective(30.0f, 4.0f / 3.0f, 0.1f, 5000.0f);
				projectionStack.LoadMatrix(projection);
				camera.MouseSensitivity = 0.1f;
				isZoom = true;
			}
			rightClick.resetTime();
		}

		if (Application::IsKeyPressed(VK_RBUTTON) && isZoom == true && rightClick.TimeCountDown(dt) < 0)
		{
			if (player.WeaponState == 2)
			{
				Mtx44 projection;
				projection.SetToPerspective(70.0f, 4.0f / 3.0f, 0.1f, 5000.0f);
				projectionStack.LoadMatrix(projection);
				isZoom = false;
				camera.MouseSensitivity = 0.2f;
			}
			rightClick.resetTime();
		}

		//framerate
		framerate << "Framerate:" << 1 / dt;

		//resources
		resources << "Resources: " << player.getResources();

		//rotation of skybox
		if (skyBoxRotate < 360.f)
		{
			skyBoxRotate += (float)dt;
		}
		else
		{
			skyBoxRotate = 0.f;
		}
		// flag rising up when get close
		if (f.getMagnitude(camera.position) <= 7.5f)
		{
			if (f.flagIsBlue == true)
			{
				if (f.FlagHeightIncrease(2.5f, dt) >= 2.5f)
				{
					isCaptured = true;
				};
			}
			else if (f.FlagHeightDecrease(0.5f, dt) <= 0.5f)
			{
				f.flagIsBlue = true;
				isCapturing = true;
			}
		}
		else
		{
			isCapturing = false;
		}
		//Astronaut
		if (Application::IsKeyPressed('E') && ((getMagnitude(a.GetAstronautPos(), camera.position)) < 3))
		{
			gameState = GS_ASTRONAUT_INTERACTION;
		}

		if (Application::IsKeyPressed('T'))
		{
			player.TakeDmg(1);
			cout << player.GetHp() << endl;
		}

		// backface culling
		if (Application::IsKeyPressed('7')) //enable back face culling
			glEnable(GL_CULL_FACE);
		if (Application::IsKeyPressed('8')) //disable back face culling
			glDisable(GL_CULL_FACE);
		if (Application::IsKeyPressed('9'))
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
		if (Application::IsKeyPressed('0'))
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

		//reset everything
		if (Application::IsKeyPressed('R'))
		{
			f.flagIsBlue = false;
			f.flagheight = 2;
		}
	}
}

void Assignment3::RenderMesh(Mesh*mesh, bool enableLight) // rendering of meshes
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

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void Assignment3::RenderSkybox() // rendering of skybox
{
	modelStack.PushMatrix();
	modelStack.Rotate(skyBoxRotate*2, 1, 1, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0, -499, 0);
	modelStack.Scale(1001, 1001, 1001);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 500, 0);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(1005, 1005, 1005);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 499);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(1000, 1000, 1000);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -499);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(1001, 1001, 1001);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(499, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(1001, 1001, 1001);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-499, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(1001, 1001, 1001);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void Assignment3::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.3f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void Assignment3::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.3f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();


	glEnable(GL_DEPTH_TEST);
}

void Assignment3::RenderModelOnScreen(Mesh *mesh, bool enableLight, Vector3 size, float x, float y, float z, Vector3 rotation) // used to render pickaxe on screen
{

	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -30, 30); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);

	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Translate(x, y, z);
	modelStack.Scale(size.x, size.y, size.z);
	modelStack.Rotate(rotation.x, 1, 0, 0);
	modelStack.Rotate(rotation.y, 0, 1, 0);
	modelStack.Rotate(rotation.z, 0, 0, 1);
	
	RenderMesh(mesh, enableLight);

	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void Assignment3::Render()
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

	if (light[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}


	if (light[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (light[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}

	//skybox
	RenderSkybox();

	//axes
	RenderMesh(meshList[GEO_AXES], false);

	//floor
	modelStack.PushMatrix();
	modelStack.Translate(0, -1, 0);
	modelStack.Scale(300, 1, 300);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(10, 3, 0);
	modelStack.Scale(0.1, 0.1, 0.1);
	RenderMesh(meshList[GEO_SNIPERRIFLE], true);
	modelStack.PopMatrix();

	//POLE
	modelStack.PushMatrix();
	modelStack.Scale(1.5, 2, 1.5);
	modelStack.PushMatrix();
	modelStack.Scale(2, 2, 2);
	modelStack.Translate(0, f.position.y - 1, f.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_FLAGPOLE], true);
	modelStack.PopMatrix();

	//FLAG
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

	//CRATERS;
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
	//TURRETS
	for (size_t i = 0; i < Turrets.size(); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Turrets[i].GetPosition().x, Turrets[i].GetPosition().y-1, Turrets[i].GetPosition().z);
		modelStack.Scale(0.3f, 0.3f, 0.3f);
		RenderMesh(meshList[GEO_TURRETBASE], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		//std::cout << Turrets[i].turretRotation << std::endl;
		modelStack.Translate(Turrets[i].GetPosition().x, Turrets[i].GetPosition().y-0.7f, Turrets[i].GetPosition().z);
		modelStack.Rotate(Turrets[i].turretRotation, 0, 1, 0);
		modelStack.Scale(0.3f, 0.3f, 0.3f);
		RenderMesh(meshList[GEO_TURRETHEAD], true);
		modelStack.PopMatrix();

		if (Turrets[i].GetShooting() == true)
		{
			//std::cout << Turrets[i].bulletPos << std::endl;
			modelStack.PushMatrix();
			modelStack.Translate(Turrets[i].bulletPos.x, Turrets[i].bulletPos.y, Turrets[i].bulletPos.z);
			modelStack.Scale(0.1f, 0.1f, 0.1f);
			RenderMesh(meshList[GEO_BULLET], true);
			modelStack.PopMatrix();
		}
	}

	//ASTRONAUT
	modelStack.PushMatrix();
	modelStack.Translate(a.GetAstronautPos().x, a.GetAstronautPos().y, a.GetAstronautPos().z);
	modelStack.Scale(0.3f, 0.3f, 0.3f);
	RenderMesh(meshList[GEO_ASTRONAUT], true);
	modelStack.PopMatrix();

	if (gameState == GS_ASTRONAUT_INTERACTION)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_UI], false, Vector3(50, 10, 1), 40, 30, 2, Vector3(90, 0, 0));
		RenderTextOnScreen(meshList[GEO_TEXT], "Upgrade Weapon?", Color(1, 0, 1), 5, 6, 5.7f);
		modelStack.PopMatrix();
	}

	//ALIEN
	for (size_t i = 0; i < Aliens.size(); ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Aliens[i].position.x, Aliens[i].position.y, Aliens[i].position.z);
		modelStack.Rotate(Aliens[i].findDirection(), 0, 1, 0);
		modelStack.Scale(Aliens[i].EnemySize, 1, Aliens[i].EnemySize);
		RenderAlien(Aliens[i].armRotate);
		modelStack.PopMatrix();

		if (Aliens[i].GetShooting() == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(Aliens[i].bulletPos.x, Aliens[i].bulletPos.y, Aliens[i].bulletPos.z);
			modelStack.Scale(0.1f, 0.1f, 0.1f);
			RenderMesh(meshList[GEO_BULLET], true);
			modelStack.PopMatrix();
		}
	}


	// ROCKS
	for (size_t i = 0; i < Rocks.size(); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Rocks[i].position.x, Rocks[i].position.y, Rocks[i].position.z);
		modelStack.Scale(Rocks[i].Size, Rocks[i].Size, Rocks[i].Size);
		RenderMesh(meshList[GEO_ROCK], true);
		modelStack.PopMatrix();
	}

	for (int i = 0; i < pistol.AmmoInClip; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(pistol.Magazine[i].getPosition().x, pistol.Magazine[i].getPosition().y, pistol.Magazine[i].getPosition().z);
		modelStack.Scale(0.1f, 0.1f, 0.1f);
		RenderMesh(meshList[GEO_BULLET], true);
		modelStack.PopMatrix();
	}

	//SPACESHIP
	if (f.flagIsBlue)
	{
		modelStack.PushMatrix();
		modelStack.Translate(ship.position.x, -1 + ship.position.y, ship.position.z);
		RenderMesh(meshList[GEO_SPACESHIP], true);
		modelStack.PopMatrix();
	}

	if (ship.displayFade)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_FADE],false, Vector3(ship.fadesize,ship.fadesize,ship.fadesize),0,0,0,Vector3(90,0,0));
		modelStack.PopMatrix();
	}


	//Aliens HP
	for (int i = 0; i < Aliens.size(); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Aliens[i].position.x - 0.25, Aliens[i].position.y + 0.5, Aliens[i].position.z);
		modelStack.Rotate(Aliens[i].findDirection() - 180, 0, 1, 0);
		modelStack.Scale(0.5, 0.5, 0.5);
		RenderText(meshList[GEO_TEXT], std::to_string(Aliens[i].GetEnemyHp()), Color(0, 1, 0));
		modelStack.PopMatrix();
	}

	// Weapons
	if (player.WeaponState == 1)
		RenderModelOnScreen(meshList[GEO_PICKAXE], true, Vector3(10.f,10.f,10.f), 70.f, 0.f, 5, Vector3(0, -45.f, player.getMiningAction()));
	else if (player.WeaponState == 2)
		RenderModelOnScreen(meshList[GEO_GUN], true, Vector3(25.f, 25.f, 25.f), 60.f, 5.f, -1, Vector3(10.f, 15.f, 0.f));

	// Message appears when u mine rocks
	if (player.isMining)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT],"+" + std::to_string(resourceOfRock)+" Resources", Color(0, 1, 0), 3, 11.5, 15);
		modelStack.PopMatrix();
	}
	if (KillMessage.GetTimeNow() >0)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "+" + std::to_string(Alienresources) + " Resources", Color(0, 1, 0), 3, 11.5, 15);
		modelStack.PopMatrix();
	}

	// Indicator for Mining
	if (player.isMining || pistol.hit)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_HITORNOT], false, 3.f, 39.9f, 29.9f, 6, Vector3(90, 0, 0));
		modelStack.PopMatrix();
	}

	// crosshair
	modelStack.PushMatrix();
	RenderTextOnScreen(meshList[GEO_CROSSHAIR], "+", Color(0, 1, 0), 3.f, 13.1f, 9.5f);
	modelStack.PopMatrix();

	//UI Screen & Player Health
	modelStack.PushMatrix();
	glBlendFunc(1.5, 1);
	RenderModelOnScreen(meshList[GEO_UI], false, Vector3(82, 10, 50), 40, 5, 6, Vector3(90, 0, 0));
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	modelStack.PushMatrix();
	RenderModelOnScreen(meshList[GEO_HEALTH], false, Vector3(player.GetHp() * 0.2, 2, -1), 22 - (100 - player.GetHp())*0.1, 7, 7, Vector3(90, 0, 0));
	RenderTextOnScreen(meshList[GEO_TEXT], "HP: ", Color(1, 0, 1), 2, 4, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(player.GetHp()), Color(1, 0, 1), 2, 5, 3);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	// INFO
	if (isShown == true)
	{
		modelStack.PushMatrix();
		glBlendFunc(1.5, 1);
		RenderModelOnScreen(meshList[GEO_INFO], false, Vector3(40, 40, 40), 40, 30, 6, Vector3(90, 270, 0));
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		modelStack.PopMatrix();
	}

	if (Application::IsKeyPressed(VK_F1) && infoscreen.GetTimeNow() <= 0)
	{
		if (isShown == false)
		{
			isShown = true;
		}
		else
			isShown = false;
		infoscreen.resetTime();
	}
	
	// FRAMERATE
	modelStack.PushMatrix();
	RenderTextOnScreen(meshList[GEO_TEXT], framerate.str(), Color(1, 0, 1), 2, 4, 1);

	modelStack.PopMatrix();
	//RESOURCES
	modelStack.PushMatrix();
	RenderTextOnScreen(meshList[GEO_TEXT], resources.str(), Color(1, 0, 1), 2, 4, 2);
	modelStack.PopMatrix();

	if (f.getMagnitude(camera.position) <= 7.5f)
	{
		if (isCaptured == false)
		{
			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Capturing Flag...", Color(0, 1, 0), 5, 6, 10);
			modelStack.PopMatrix();
		}
		else
		{
			modelStack.PushMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Flag Captured!", Color(0, 1, 0), 5, 6, 10);
			modelStack.PopMatrix();
		}
	}
}

void Assignment3::RenderAlien(float armRotate)
{
	modelStack.PushMatrix();
	modelStack.Translate(0.f, -3.2f, 0.f);
	RenderMesh(meshList[GEO_ALIENHEAD], true);
	RenderMesh(meshList[GEO_ALIENBODY], true);
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 2.9f, 0.f);
	modelStack.Rotate(armRotate, 1, 0, 0);
	modelStack.Translate(0.f, -2.9f, 0.f);
	modelStack.PushMatrix(); // arms
	modelStack.Translate(-0.3f, 2.7f, 0.f);
	modelStack.Scale(0.2f, 0.4f, 0.4f);
	RenderMesh(meshList[GEO_ALIENPART], true);
	modelStack.PushMatrix();
	modelStack.Translate(3, 0, 0);
	RenderMesh(meshList[GEO_ALIENPART], true);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void Assignment3::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}