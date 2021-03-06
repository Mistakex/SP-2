/******************************************************************************/
/*!
\file	SP2.cpp
\author 
\par	email:
\brief
The entire SP2 scene
*/
/******************************************************************************/

#include "SP2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "LoadTGA.h"
#include "Utility.h"


#include <stdlib.h>
#include <sstream>

#include "Music.h"


using std::cout;
using std::endl;

/******************************************************************************/
/*!
\brief
Default constructor of scene
*/
/******************************************************************************/

SP2::SP2()
{
}

/******************************************************************************/
/*!
\brief
Default destructor of scene
*/
/******************************************************************************/

SP2::~SP2()
{
}

/******************************************************************************/
/*!
\brief
Gets the magnitude between two vector3s
\param object
One of the objects
\param target
The other object
\return
Returns the distance between the two Vector3s
*/
/******************************************************************************/

float SP2::getMagnitude(const Vector3 object, const Vector3 target)
{
	Vector3 a;
	a.x = object.x - target.x;
	a.y = object.y - target.y;
	a.z = object.z - target.z;
	return sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
}

/******************************************************************************/
/*!
\brief
Restarts the scene's variables
*/
/******************************************************************************/

void SP2::restartScene()
{
	// Pauses the sound
	sound.pause();

	// Resets the flag
	f.flagIsBlue = false;
	f.flagheight = 2.5;
	isCapturing = false;
	isCaptured = false;

	// Resets boss
	bossDead = false;
	Boss.EnemySetHp(3000);
	Boss.bossIsSpawned = false;
	

	// Resets Player
	playDead = false;
	player.gameOver();
	camera.Reset();

	// Resets astronaut upgrades(upgrade cost and damage)
	a.resetAllUpgrades();
	a.resetWeaponUpgrades(pistol);
	a.resetWeaponUpgrades(SniperRifle);
	a.resetMedkitUpgrades(medKit);
	EmptyVector();

	// changes gameState back to main
	gameState = GS_MAIN;
	CameraMouseUpdate = true;
}

/******************************************************************************/
/*!
\brief
Initializes the variables in SP2
*/
/******************************************************************************/

void SP2::Init()
{
	gameState = GS_MAIN;
	CameraMouseUpdate = true;
	player.WeaponState = 2;
	player.noOfGrenadesHeld = 5;
	pistol.init(&camera,&Pillars);
	ship.init(&camera);
	SniperRifle.init(&camera,&Pillars);

	sound.playSoundThreaded("Music/spawn.mp3");

	Boss = Enemy(Vector3(0, 0, 0), camera.position, Vector3(5, 10, 5), 3000, 10, 0, 1000, 10,true);

	//srand
	KillMessage.TimeCountDown(0.3);
	srand(time_t(NULL));
	for (float i = 0; i < 3; ++i)
	{
		Aliens.push_back(Enemy(Vector3(i * 2, 0, i * 2), Vector3(0, 0, 0), Vector3(0.5, 1, 0.5)));
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
	light[0].color.Set(1, 0.9f, 1);
	light[0].position.Set(0.f, -5.f, 0.f);
	light[0].power = 0.95f;
	light[0].kC = 1.f;
	light[0].kL = 0.1f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.0f, 1.0f, 0.0f);

	light[1].type = Light::LIGHT_DIRECTIONAL;

	light[1].color.Set(1, 1, 1);
	light[1].position.Set(0.f, 15.f, 0.f);
	light[1].power = 0.5;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(30));
	light[1].cosInner = cos(Math::DegreeToRadian(10));
	light[1].exponent = 3.f;

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
	camera.Init(Vector3(0, 0, 30), Vector3(10, 0, 0), Vector3(0, 1, 0), &Rocks, &f,&Pillars);

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

	meshList[GEO_ALIENHEADred] = MeshBuilder::GenerateOBJ("alienhead", "OBJ//alienhead.obj");
	meshList[GEO_ALIENHEADred]->textureID = LoadTGA("Image//ALIENHEADred.tga");

	meshList[GEO_ALIENPARTred] = MeshBuilder::GenerateOBJ("alienpart", "OBJ//alienpart.obj");
	meshList[GEO_ALIENPARTred]->textureID = LoadTGA("Image//ALIENBODYred.tga");

	meshList[GEO_ALIENBODYred] = MeshBuilder::GenerateOBJ("alienbody", "OBJ//alienbody.obj");
	meshList[GEO_ALIENBODYred]->textureID = LoadTGA("Image//ALIENBODYred.tga");

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

	meshList[GEO_UI] = MeshBuilder::GenerateQuad("UI Screen", Color(1, 1, 1));
	meshList[GEO_UI]->textureID = LoadTGA("Image//UI_Frame.tga");

	meshList[GEO_INFO] = MeshBuilder::GenerateQuad("Info", Color(1, 1, 1));
	meshList[GEO_INFO]->textureID = LoadTGA("Image//instructions.tga");

	meshList[GEO_HEALTH] = MeshBuilder::GenerateQuad("Health", Color(1, 0, 1));

	meshList[GEO_SPACESHIP] = MeshBuilder::GenerateOBJ("Spaceship", "OBJ//SpaceObject.obj");
	meshList[GEO_SPACESHIP]->textureID = LoadTGA("Image//SpaceObjectUV.tga");

	meshList[GEO_SNIPERRIFLE] = MeshBuilder::GenerateOBJ("/SniperRifle", "OBJ//SniperRifle.obj");
	meshList[GEO_SNIPERRIFLE]->textureID = LoadTGA("Image//SniperRifle.tga");

	meshList[GEO_FADE] = MeshBuilder::GenerateQuad("Fade", Color(1, 1, 1));

	meshList[GEO_DOME] = MeshBuilder::GenerateOBJ("Dome", "OBJ//dome.obj");
	meshList[GEO_DOME]->textureID = LoadTGA("Image//domeUV.tga");

	meshList[GEO_ZOOM] = MeshBuilder::GenerateQuad("Zoom", Color(1, 1, 1));
	meshList[GEO_ZOOM]->textureID = LoadTGA("Image//scope.tga");

	meshList[GEO_GRENADE] = MeshBuilder::GenerateOBJ("Grenade", "OBJ//Grenade.obj");
	meshList[GEO_GRENADE]->textureID = LoadTGA("Image//Grenade.tga");

	meshList[GEO_MEDKIT] = MeshBuilder::GenerateOBJ("Medkit", "OBJ//Medkit.obj");
	meshList[GEO_MEDKIT]->textureID = LoadTGA("Image//Medkit.tga");

	meshList[GEO_HARVESTOR] = MeshBuilder::GenerateOBJ("Harvestor", "OBJ//Harvestor.obj");
	meshList[GEO_HARVESTOR]->textureID = LoadTGA("Image//Harvestor.tga");

	meshList[GEO_PILLAR] = MeshBuilder::GenerateCylinder("Pillar", Color(1, 1, 1), 30);

	meshList[GEO_SPACETRUCK] = MeshBuilder::GenerateOBJ("Spacetruck", "OBJ//LandObject.obj");
	meshList[GEO_SPACETRUCK]->textureID = LoadTGA("Image//LandObject.tga");

	meshList[GEO_MOUNTAIN] = MeshBuilder::GenerateOBJ("Mountain", "OBJ//mountain.obj");
	meshList[GEO_MOUNTAIN]->textureID = LoadTGA("Image//mountain.tga");
	
	meshList[GEO_WATERTANK] = MeshBuilder::GenerateOBJ("Watertank", "OBJ//Watertank.obj");
	meshList[GEO_WATERTANK]->textureID = LoadTGA("Image//Watertank.tga");

	meshList[GEO_SHOPBANNER] = MeshBuilder::GenerateOBJ("Shopbanner", "OBJ//Flag.obj");
	meshList[GEO_SHOPBANNER]->textureID = LoadTGA("Image//Shopbanner.tga");

	Mtx44 projection;
	projection.SetToPerspective(70.0f, 4.0f / 3.0f, 0.1f, 5000.0f);
	projectionStack.LoadMatrix(projection);
	
	// Sets the words for Astronaut Options
	AstronautOpt[OPT_UP_PISTOL] = "Upgrade Pistol?";
	AstronautOpt[OPT_UP_RIFLE] = "Upgrade S. Rifle?";
	AstronautOpt[OPT_UP_TURRET] = "Upgrade Turret?";
	AstronautOpt[OPT_UP_NADE_DMG] = "Upgrade Grenade Damage?";
	AstronautOpt[OPT_UP_NADE_RANGE] = "Upgrade Grenade Range?";
	AstronautOpt[OPT_UP_MEDKIT_TICKS] = "Upgrade Medkit Ticks?";
	AstronautOpt[OPT_UP_MEDKIT_HEAL] = "Upgrade Medkit Recovery?";
	AstronautOpt[OPT_BUY_HARVESTOR] = "Purchase a Harvestor?";
	AstronautOpt[OPT_BUY_GRENADES] = "Purchase a Grenade?";
	AstronautOpt[OPT_BACK_TO_MAIN] = "Back to Game?";

	// Sets words for Pause Menu(includes death and restart menu)
	PauseOpt[P_OPT_UNPAUSE] = "Unpause?";
	PauseOpt[P_OPT_RESTART] = "Restart?";
	PauseOpt[P_OPT_QUITGAME] = "Quit Game?";
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

static float LSPEED = 10.f; // LIGHT SPEED

static float skyBoxRotate = 0.f; // rotation of skybox

static std::stringstream framerate;
static std::stringstream resources;

/******************************************************************************/
/*!
\brief
Updates everything in SP2 every frame
\param dt
The time in between each frame
*/
/******************************************************************************/

void SP2::Update(double dt)
{
	if (Application::IsKeyPressed('Z'))
	{
		std::cout << camera.position.x << std::endl;
		std::cout << camera.position.z << std::endl;
		dt = dt * 20;
		player.ObtainResources(30);
	}
	if (gameState == GS_MAIN || gameState == GS_ASTRONAUT_INTERACTION)
	{
		camera.OnControls = true;
		Scene1Updates(dt);
	}
	if (gameState == GS_SCENE2)
	{
		Scene2Updates();
	}
	if (gameState == GS_SCENE3)
	{
		Scene3Updates();
	}

	ship.cutscene(dt);
	if (ship.changeScene && gameState == GS_MAIN)
	{
		gameState = GS_SCENE2;
	}

	// Checks if player is dead and changes the gamestate accordingly
	/*******************HP = 0*******************/
	if (player.isDead())
	{
		if (player.Retry <= 0)
		{
			CameraMouseUpdate = false;
			gameState = GS_GAMEOVER;
			return;
		}
		gameState = GS_DIED;
	}

	if (gameState == GS_DIED)
	{
		if (playDead == false)
		{
			sound.pause();
			playDead = true;
			sound.playSoundThreaded("Music/death.mp3");
		}
		if (Application::IsKeyPressed(VK_RETURN))
		{
			gameState = GS_MAIN;
			Boss.bossIsSpawned = false;
			player.reset();
			player.Retry -= 1;
			EmptyVector();
			camera.Reset();
			playDead = false;
		}
		camera.OnControls = false;
	}

	if (Application::IsKeyPressed('P') && gameState != GS_PAUSE)
	{
		if (tempGS != GS_PAUSE)
		{
			tempGS = gameState;
		}
		gameState = GS_PAUSE;
	}

	// GS PAUSE
	if (gameState == GS_PAUSE)
	{
		CameraMouseUpdate = false;
		debouncePauseUI.TimeCountDown(dt);
		if (((Application::IsKeyPressed('S')) || (Application::IsKeyPressed(VK_DOWN))) && (debouncePauseUI.GetTimeNow() <= 0))
		{
			if (pauseScreenCursor != (NUM_PAUSE_OPTIONS - 1))
			{
				pauseScreenCursor++;
			}
			else
			{
				pauseScreenCursor = 0;
			}
			debouncePauseUI.resetTime();
		}
		if (((Application::IsKeyPressed('W')) || (Application::IsKeyPressed(VK_UP))) && (debouncePauseUI.GetTimeNow() <= 0))
		{
			if (pauseScreenCursor != 0)
			{
				pauseScreenCursor--;
			}
			else
			{
				pauseScreenCursor = NUM_PAUSE_OPTIONS - 1;
			}
			debouncePauseUI.resetTime();
		}
		if (Application::IsKeyPressed(VK_RETURN) && debouncePauseUI.GetTimeNow() <= 0)
		{
			switch (pauseScreenCursor)
			{
			case(P_OPT_UNPAUSE) :
				gameState = tempGS;
				CameraMouseUpdate = true;
				break;
			case(P_OPT_RESTART) :
				restartScene();
				break;
			case(P_OPT_QUITGAME) :
				quitGame = true;
				break;
			}
		}
	}

	// Gameover screen
	if (gameState == GS_GAMEOVER)
	{
		if (playDead == false)
		{
			sound.pause();
			playDead = true;
			sound.playSoundThreaded("Music/death.mp3");
		}
		CameraMouseUpdate = false;
		camera.OnControls = false;
		debouncePauseUI.TimeCountDown(dt);
		if (((Application::IsKeyPressed('S')) || (Application::IsKeyPressed(VK_DOWN))) && (debouncePauseUI.GetTimeNow() <= 0))
		{
			if (quitGameCursor == 0)
			{
				quitGameCursor = 1;
			}
			else
			{
				quitGameCursor = 0;
			}
			debouncePauseUI.resetTime();
		}
		if (((Application::IsKeyPressed('W')) || (Application::IsKeyPressed(VK_UP))) && (debouncePauseUI.GetTimeNow() <= 0))
		{
			if (quitGameCursor == 0)
			{
				quitGameCursor = 1;
			}
			else
			{
				quitGameCursor = 0;
			}
			debouncePauseUI.resetTime();
		}
		if (Application::IsKeyPressed(VK_RETURN) && debouncePauseUI.GetTimeNow() <= 0)
		{
			switch (quitGameCursor)
			{
			case(P_OPT_RESTART) :
				restartScene();
				break;
			case(P_OPT_QUITGAME) :
				quitGame = true;
				break;
			}
		}
	}

	
	/********************************************/

	infoscreen.TimeCountDown(dt);

	//mouse rotation of camera
	if (CameraMouseUpdate == true)
	{
		camera.Update(dt,static_cast<int>(gameState));
		framerate.str("");
		resources.str("");
		////*********************************************////
		pistol.update(dt);
		SniperRifle.update(dt);
		debounce.TimeCountDown(dt);

		// SniperRifle
		if (Application::IsKeyPressed('1') && debounce.GetTimeNow() < 0)
		{
			debounce.resetTime();
			player.WeaponState = 1;
		}

		// Pistol
		if (Application::IsKeyPressed('2') && debounce.GetTimeNow() < 0)
		{
			debounce.resetTime();
			player.WeaponState = 2;
		}

		// Pickaxe
		if (Application::IsKeyPressed('3') && debounce.GetTimeNow() < 0)
		{
			debounce.resetTime();
			player.WeaponState = 3;
		}

		// Turrets
		if (Application::IsKeyPressed('4') && debounce.GetTimeNow() < 0)
		{
			debounce.resetTime();
			player.WeaponState = 4;
		}

		// Grenades and medkit
		if (Application::IsKeyPressed('5') && debounce.GetTimeNow() < 0)
		{
			debounce.resetTime();
			if (player.WeaponState == 5)
			{
				player.WeaponState = 6;
			}
			else
			{
				player.WeaponState = 5;
			}
		}

		if (gameState == GS_MAIN || gameState == GS_ASTRONAUT_INTERACTION || gameState == GS_SCENE2)
		{
			//Alien Spawn
			AlienSpawn(dt);
			KillMessage.TimeCountDown(dt);
			//Alien update
			AlienUpdate(dt);
			//Rocks spawn
			RockSpawn(dt);
		}
		else if (gameState == GS_SCENE3)
		{
			KillMessage.TimeCountDown(dt);
			AlienUpdate(dt);
			if (Boss.GetEnemyHp() > 0)
			{
				Boss.update(camera, dt, &player, &Turrets);
			}
		}
		//Turrets Aim and Shoot
		TurretUpdate(dt);
		//Rock mining
		player.WhileMining(dt);
		//Harvestor
		HarvestorUpdate(dt);
		//Grenades
		GrenadeUpdate(dt);
		//Medkits
		medKit.Activated();
		medKit.Heal(player);
		medKit.TimerUpdate(dt);
		//Timers
		countdownMining.TimeCountDown(dt);
		countdownTurretSpawn.TimeCountDown(dt);
		countdownPistol.TimeCountDown(dt);
		CountdownSniperRifle.TimeCountDown(dt);
		GrenadeThrowDelay.TimeCountDown(dt);
		if (Application::IsKeyPressed('E'))
		{
			if (getMagnitude(ship.position, camera.position) < 8.f && isCaptured == true)
			{
				EmptyVector();
				camera.Reset();
				ship.updateCutscene = true;
			}
		}
		if (Application::IsKeyPressed(VK_LBUTTON) && !ship.updateCutscene) //check for keypress and weapon holding
		{
			if (player.WeaponState == 1 && CountdownSniperRifle.GetTimeNow() <= 0)
			{
				SniperRifle.FireSR(&Aliens,&Boss);
				sound.playSoundThreaded("Music/sniper.mp3");
				CountdownSniperRifle.resetTime();
			}
			if (player.WeaponState == 2 && countdownPistol.GetTimeNow() <= 0)
			{
				pistol.Fire(&Aliens,&Boss);
				sound.playSoundThreaded("Music/pew.mp3");
				countdownPistol.resetTime();
			}
			if (player.WeaponState == 3 && (Rocks.empty() == 0) && (countdownMining.GetTimeNow() <= 0))
			{
				MiningUpdate();
			}
			else if (player.WeaponState == 4 && countdownTurretSpawn.GetTimeNow() <= 0 && player.getResources() >= 50)
			{
				TurretSpawn();	
			}
			else if (player.WeaponState == 5 && GrenadeThrowDelay.GetTimeNow() <= 0)
			{
				// If player has no Grenades at all.
				if (player.noOfGrenadesHeld > 0)
				{
					sound.decreaseVolume();
					sound.playSoundThreaded("Music/throwgrenade.wav");
					GrenadesFlying.push_back(Grenade(Vector3(camera.position.x, camera.position.y, camera.position.z), Vector3(camera.target.x, camera.target.y, camera.target.z), a.GrenadeDamage, a.GrenadeRange, 3.0f));
					GrenadeThrowDelay.resetTime();
					player.noOfGrenadesHeld--;					
				}
			}
			else if (player.WeaponState == 6 && medKit.activated == false)
			{
				medKit.activated = true;
				player.WeaponState = 1;
				CountdownSniperRifle.resetTime();
			}
		}
		rightClick.TimeCountDown(dt);
		if (Application::IsKeyPressed(VK_RBUTTON) && rightClick.GetTimeNow() < 0 && !ship.updateCutscene)
		{
			if (player.WeaponState == 1)
			{
				sound.playSoundThreaded("Music/zoom.mp3");
				if (isZoom == false)
				{
					Mtx44 projection;
					projection.SetToPerspective(10.0f, 4.0f / 3.0f, 0.1f, 5000.0f);
					projectionStack.LoadMatrix(projection);
					camera.MouseSensitivity = 0.02f;
					isZoom = true;
				}
				else
				{
					Mtx44 projection;
					projection.SetToPerspective(70.0f, 4.0f / 3.0f, 0.1f, 5000.0f);
					projectionStack.LoadMatrix(projection);
					camera.MouseSensitivity = 0.2f;
					isZoom = false;
				}
			}
			rightClick.resetTime();
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

		if (isZoom == true)
		{
			if (player.WeaponState != 1)
			{
				Mtx44 projection;
				projection.SetToPerspective(70.0f, 4.0f / 3.0f, 0.1f, 5000.0f);
				projectionStack.LoadMatrix(projection);
				isZoom = false;
				camera.MouseSensitivity = 0.2f;
			}
		}

		if (Boss.isDead() == true && bossDead == false)
		{
			sound.pause();
			bossDead = true;
			sound.increaseVolume();
			sound.playSoundThreaded("Music/bossdie.mp3");
		}

		//framerate
		framerate << "Framerate:" << 1 / dt;

		//resources
		resources << "Resources: " << player.getResources();

		//rotation of skybox
		if (gameState != GS_SCENE3)
		{
			if (skyBoxRotate < 360.f)
			{
				skyBoxRotate += (float)dt;
			}
			else
			{
				skyBoxRotate = 0.f;
			}
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
	}
}

/******************************************************************************/
/*!
\brief
Used to render meshes
\param *mesh
The mesh to render
\param enableLight
Whether or not to enable light for the mesh
*/
/******************************************************************************/

void SP2::RenderMesh(Mesh*mesh, bool enableLight) // rendering of meshes
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

/******************************************************************************/
/*!
\brief
Rendering of Skybox
*/
/******************************************************************************/

void SP2::RenderSkybox() // rendering of skybox
{
	modelStack.PushMatrix();
	modelStack.Rotate(skyBoxRotate * 2, 1, 1, 0);
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

/******************************************************************************/
/*!
\brief
Rendering of text
\param *mesh
Mesh to render
\param text
Text to render
\param color
Color of text to render
*/
/******************************************************************************/

void SP2::RenderText(Mesh* mesh, std::string text, Color color)
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

/******************************************************************************/
/*!
\brief
Rendering of text on screen
\param *mesh
Mesh to render
\param text
Text to render
\param color
Color of text to render
\param size
Size of the text
\param x
x-coordinate of the text
\param y
y-coordinate of the text
*/
/******************************************************************************/

void SP2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

/******************************************************************************/
/*!
\brief
Rendering of model on screen
\param *mesh
Mesh to render
\param enableLight
Whether or not to enable light
\param size
Size of the model on the screen
/param x
X-coordinate of model
/param y
Y-coordinate of model
/param z
Z-coordinate of model
/param rotation
Rotation of the model on screen
*/
/******************************************************************************/

void SP2::RenderModelOnScreen(Mesh *mesh, bool enableLight, Vector3 size, float x, float y, float z, Vector3 rotation) // used to render pickaxe on screen
{

	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -100, 70); //size of screen UI
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

/******************************************************************************/
/*!
\brief
Rendering everything in the scene
*/
/******************************************************************************/

void SP2::Render()
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
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}


	//skybox
	if (gameState != GS_SCENE3)
	{
		RenderSkybox();
	}
	//Watertank
	if (gameState == 2)
	{
		modelStack.PushMatrix();
		modelStack.Translate(40, -1, 0);
		modelStack.Scale(3, 3, 3);
		RenderMesh(meshList[GEO_WATERTANK], true);
		modelStack.PopMatrix();
	}
	// mountains
	for (int i = 0; i < 360; i += 30)
	{
		modelStack.PushMatrix();
		modelStack.Rotate(i, 0, 1.f, 0);
		modelStack.Translate(250, -10, 0);
		modelStack.Scale(100, 100, 100);
		RenderMesh(meshList[GEO_MOUNTAIN], true);
		modelStack.PopMatrix();
	}

	//axes
	//RenderMesh(meshList[GEO_AXES], false);

	//floor
	modelStack.PushMatrix();
	modelStack.Translate(0, -1, 0);
	modelStack.Scale(350, 1, 350);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	if (gameState == GS_MAIN || gameState == GS_ASTRONAUT_INTERACTION)
	{
		Scene1Render();	//flag ,pole , astronaut, crater render
	}

	RenderAstronautInteractions();

	//Harvestors
	for (unsigned int i = 0; i < a.Harvestor.size(); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(a.Harvestor[i].Position.x, 0, a.Harvestor[i].Position.z);
		modelStack.Rotate(a.Harvestor[i].GetHarvestorRotation(), 0, 1, 0);
		modelStack.Scale(1, 1, 1);
		RenderMesh(meshList[GEO_HARVESTOR], true);
		modelStack.PopMatrix();
	}
	//GRENADES
	for (unsigned int i = 0; i < GrenadesFlying.size(); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(GrenadesFlying[i].GetPosition().x, GrenadesFlying[i].GetPosition().y, GrenadesFlying[i].GetPosition().z);
		modelStack.Rotate(GrenadesFlying[i].LookAtDirection, 0, 0, 1);
		modelStack.Rotate(GrenadesFlying[i].GrenadeRotation, 1, 0, 0);
		modelStack.Scale(0.1f, 0.1f ,0.1f);
		RenderMesh(meshList[GEO_GRENADE], true);
		modelStack.PopMatrix();

		if (GrenadesFlying[i].Explode == true && !GrenadesFlying.empty())
		{
			modelStack.PushMatrix();
			modelStack.Translate(GrenadesFlying[i].GetPosition().x, GrenadesFlying[i].GetPosition().y, GrenadesFlying[i].GetPosition().z);
			modelStack.Scale(GrenadesFlying[i].size, GrenadesFlying[i].size, GrenadesFlying[i].size);
			RenderMesh(meshList[GEO_LIGHTBALL], true);
			modelStack.PopMatrix();
		}
	}
	//TURRETS
	RenderTurret();
	//ALIEN
	RenderAliens();

	if (gameState == GS_SCENE3)
	{
		Scene3Render();
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

	for (int i = 0; i < SniperRifle.AmmoInClip; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(SniperRifle.Magazine[i].getPosition().x, SniperRifle.Magazine[i].getPosition().y, SniperRifle.Magazine[i].getPosition().z);
		modelStack.Scale(0.05f, 0.05f, 0.05f);
		RenderMesh(meshList[GEO_BULLET], true);
		modelStack.PopMatrix();
	}

	//DOME
	if (gameState == GS_SCENE2)
	{
		RenderDome(10, 0, -1, 0);
	}

	//Aliens HP
	for (unsigned int i = 0; i < Aliens.size(); i++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Aliens[i].position.x, Aliens[i].position.y + 0.5f, Aliens[i].position.z);
		modelStack.Rotate(Aliens[i].findDirection() - 180, 0, 1, 0);
		modelStack.Scale(0.5, 0.5, 0.5);
		RenderText(meshList[GEO_TEXT], std::to_string(Aliens[i].GetEnemyHp()), Color(0, 1, 0));
		modelStack.PopMatrix();
	}
	// Boss HP
	if (gameState == GS_SCENE3 && Boss.GetEnemyHp() > 0)
	{
		modelStack.PushMatrix();
		modelStack.Translate(Boss.position.x, Boss.position.y + 12.f, Boss.position.z);
		modelStack.Rotate(Boss.findDirection() - 180, 0, 1, 0);
		modelStack.Scale(5, 5, 5);
		RenderText(meshList[GEO_TEXT], std::to_string(Boss.GetEnemyHp()), Color(0, 1, 0));
		modelStack.PopMatrix();
	}

	// Weapons
	if (!ship.updateCutscene && isZoom == false)
	{
		if (player.WeaponState == 1)
			RenderModelOnScreen(meshList[GEO_SNIPERRIFLE], true, Vector3(10.f, 10.f, 10.f), 57.f, 0.f, 39.f, Vector3(10.f, -79.f, 0.f));
		else if (player.WeaponState == 2)
			RenderModelOnScreen(meshList[GEO_GUN], true, Vector3(22.f, 22.f, 22.f), 57.f, 3.f, -1.f, Vector3(12.f, 15.f, 0.f));
		else if (player.WeaponState == 3)
			RenderModelOnScreen(meshList[GEO_PICKAXE], true, Vector3(10.f, 10.f, 10.f), 70.f, 0.f, -10, Vector3(0, -45.f, player.getMiningAction()));
		else if (player.WeaponState == 4)
			RenderModelOnScreen(meshList[GEO_TURRETHEAD], true, Vector3(10.f, 10.f, 10.f), 54.f, 0.f, -10.f, Vector3(30.f, -45.f, -30.f));
		else if (player.WeaponState == 5 && player.noOfGrenadesHeld != 0)
			RenderModelOnScreen(meshList[GEO_GRENADE], true, Vector3(5.f, 5.f, 5.f), 60.f, 0.f, -10, Vector3(0, -45.f, 30.f));
		else if (player.WeaponState == 6)
			RenderModelOnScreen(meshList[GEO_MEDKIT], true, Vector3(15.f, 15.f, 15.f), 60.f, 0.f, -10, Vector3(30.f, 45.f, 30.f));
	}
	// SHIP DISPLAY
	if (getMagnitude(camera.position, ship.position) < 8.f && isCaptured && gameState == GS_MAIN)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Press E to fly", Color(0, 1, 0), 3, 11.5, 15);
		modelStack.PopMatrix();
	}

	// Message appears when u mine rocks
	if (player.isMining)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "+" + std::to_string(resourceOfRock) + " Resources", Color(0, 1, 0), 3, 11.5, 15);
		modelStack.PopMatrix();
	}
	if (KillMessage.GetTimeNow() >0)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "+" + std::to_string(Alienresources) + " Resources", Color(0, 1, 0), 3, 11.5, 15);
		modelStack.PopMatrix();
	}

	// Indicator for Mining
	if (player.isMining || pistol.hit || SniperRifle.hit)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_HITORNOT], false, Vector3(3.f, 3.f, 3.f), 39.9f, 29.9f, 6, Vector3(90, 0, 0));
		modelStack.PopMatrix();
	}

	// crosshair
	if (isZoom == false)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_CROSSHAIR], "+", Color(0, 1, 0), 3.f, 13.1f, 9.5f);
		modelStack.PopMatrix();
	}

	//UI for scene 3
	if (gameState == GS_SCENE3)
	{
		Scene3UI();
	}

	// UI window for astronaut / died / gameover
	if (gameState == GS_ASTRONAUT_INTERACTION || gameState == GS_DIED || gameState == GS_GAMEOVER || gameState == GS_PAUSE)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_UI], false, Vector3(45, 20, 1), 40, 30, 2, Vector3(90, 0, 0));
		modelStack.PopMatrix();
	}
	// Astronaut State interactions (shop etc)
	RenderAstronautInteractions();

	if (gameState == GS_DIED)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "You died!", Color(1, 0, 1), 4.5f, 5, 7);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press Enter to Respawn.", Color(1, 0, 1), 4.5f, 5, 6);
		modelStack.PopMatrix();
	}

	if (gameState == GS_GAMEOVER)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "You used up all your retries!", Color(1, 0, 1), 3.7f, 6, 8);
		RenderTextOnScreen(meshList[GEO_TEXT], PauseOpt[quitGameCursor], Color(1, 0, 1), 3.7f, 6, 7);
		modelStack.PopMatrix();
	}

	if (gameState == GS_PAUSE)
	{
		modelStack.PushMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Game is Paused.", Color(1, 0, 1), 3.7f, 6, 8);
		RenderTextOnScreen(meshList[GEO_TEXT], "^", Color(1, 0, 0), 3.7f, 13.f, 8.5f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Enter", Color(1, 0, 0), 3.7f, 12.5f, 7.5f);
		RenderTextOnScreen(meshList[GEO_TEXT], "v", Color(1, 0, 0), 3.7f, 13.f, 6.5f);
		RenderTextOnScreen(meshList[GEO_TEXT], PauseOpt[pauseScreenCursor], Color(1, 0, 1), 3.7f, 6, 7);
		modelStack.PopMatrix();

	}
	//UI Screen & Player Health
	if (isZoom == false)
	{
		modelStack.PushMatrix();
		glBlendFunc(static_cast<GLenum>(1.5), static_cast<GLenum>(1));
		RenderModelOnScreen(meshList[GEO_UI], false, Vector3(30, 11, 11), 14.5, 55, 5, Vector3(90, 0, 0));
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_HEALTH], false, Vector3(player.GetHp() * 0.2f, 2.f, 0.f), 22.f - (157.f - (float)player.GetHp())*0.1f, 57.7f, 7.f, Vector3(90.f, 0.f, 0.f));
		RenderTextOnScreen(meshList[GEO_TEXT], "HP: ", Color(1, 0, 1), 2.f, 1.3f, 28.3f);
		RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(player.GetHp()), Color(1, 0, 1), 2.f, 2.2f, 28.3f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Retries: ", Color(1, 0, 1), 2.f, 1.3f, 26.3f);
		RenderTextOnScreen(meshList[GEO_TEXT], std::to_string(player.Retry), Color(1, 0, 1), 2.f, 4.f, 26.3f);
		modelStack.PopMatrix();
		modelStack.PopMatrix();
	}


	// FRAMERATE
	modelStack.PushMatrix();
	RenderTextOnScreen(meshList[GEO_TEXT], framerate.str(), Color(1, 0, 1), 2.f, 1.3f, 25.3f);
	modelStack.PopMatrix();

	//RESOURCES
	modelStack.PushMatrix();
	RenderTextOnScreen(meshList[GEO_TEXT], resources.str(), Color(1, 0, 1), 2.f, 1.3f, 27.3f);
	modelStack.PopMatrix();

	// INFO
	if (isShown == true)
	{
		modelStack.PushMatrix();
		glBlendFunc(static_cast<GLenum>(1.5), static_cast<GLenum>(1));
		RenderModelOnScreen(meshList[GEO_INFO], false, Vector3(40, 40, 40), 40, 30, 6, Vector3(90, 270, 0));
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		modelStack.PopMatrix();
	}

	if (gameState == GS_MAIN)
		RenderScene1UI();

	//fadeaway
	if (ship.displayFade)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_FADE], false, Vector3(ship.fadesize, 150.f, 0), 0, 0, 12, Vector3(90, 0, 0));
		modelStack.PopMatrix();
	}

	if (isZoom == true)
	{
		modelStack.PushMatrix();
		RenderModelOnScreen(meshList[GEO_ZOOM], false, Vector3(82, 100, 0), 41, 30, 13, Vector3(90, 0, 0));
		modelStack.PopMatrix();
	}

	
}

/******************************************************************************/
/*!
\brief
Exiting the scene
*/
/******************************************************************************/

void SP2::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}