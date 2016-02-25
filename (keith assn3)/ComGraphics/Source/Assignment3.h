#ifndef ASSIGNMENT3_H
#define ASSIGNMENT3_H

#include "Scene.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "CountDown.h"
#include "Player.h"
#include "Turret.h"
#include "Enemy.h"
#include "CountDown.h"
#include "Rock.h"
#include "Flag.h"
#include "Astronaut.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Ship.h"
#include <string>
using std::string;

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
		GEO_FLAGPOLE,
		GEO_ENEMYFLAG,
		GEO_ALLYFLAG,
		GEO_UNCAPTURED,
		GEO_CAPTURED,
		GEO_CRATER,
		GEO_LIGHTBALL,
		GEO_TEXT,
		GEO_ALIENHEAD,
		GEO_ALIENBODY,
		GEO_ALIENPART,
		GEO_ROCK,
		GEO_PICKAXE,
		GEO_GUN,
		GEO_CROSSHAIR,
		GEO_HITORNOT,
		GEO_ASTRONAUT,
		GEO_PLAYERHP,
		GEO_UI,
		GEO_INFO,
		GEO_HEALTH,
		//Turret
		GEO_TURRETHEAD,
		GEO_TURRETBASE,
		//SPACESHIP
		GEO_SPACESHIP,
		//SniperRifle
		GEO_SNIPERRIFLE,
		GEO_FADE,
		GEO_ZOOM,
		//Dome
		GEO_DOME,
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

	enum GameStates
	{
		GS_MAIN,
		GS_ASTRONAUT_INTERACTION,
		GS_SCENE2,
		GS_SCENE3,
		NUM_GAMESTATES
	};

	GameStates gameState;

public:
	Assignment3();
	~Assignment3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	vector<Enemy> Aliens;
	vector<GameObject*> Collisions;
	vector<Rock> Rocks;
	vector<Turret> Turrets;
	Weapon pistol = Weapon(20, 30, 100, 10, false);
	Flag f = Flag(Vector3(0, 0.75f, 0), Vector3(1, 1, 1));
	Astronaut a = Astronaut(Vector3(5, -1, 0));
	Ship ship = Ship(Vector3(0, 0, -50), Vector3(5, 5, 5));
	Weapon SniperRifle = Weapon(150, 10, 100, 100, true);

private:
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderModelOnScreen(Mesh *mesh, bool enableLight, Vector3 size, float x, float y, float z, Vector3 rotation);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox();
	void RenderAlien(float armRotate = 0);

	void checkCollision(const Vector3 &center, float x1, float z1, float y1);
	float getMagnitude(const Vector3 user, const Vector3 target);	//find the magnitude between 2 points
	float randomx, randomz;											//random locations for the rock spawn


	//Spawn functions
	void AlienSpawn(double dt);
	void RockSpawn(double dt);
	void TurretSpawn();
	void TurretUpdate(double dt);
	void AlienUpdate(double dt);
	//Render Functions
	void RenderPole();
	void RenderFlag();
	void RenderCraters();
	void RenderTurret();
	void RenderAliens();
	void RenderAstronaut();
	void RenderDome(float scale,float x,float y,float z);
	//Scenes
	void Scene1Updates(double dt);
	void Scene1Render();
	void RenderScene1UI();
	void Scene2Updates();
	void Scene2Render();
	//Remove alien
	void EmptyVector();

	// countdown
	Countdown countdownRock = Countdown(10.0f);
	Countdown countdownMining = Countdown(0.5f);
	Countdown countdownPistol = Countdown(0.5f);
	Countdown countdownAlienSpawn = Countdown(10.f);
	Countdown debounce = Countdown(0.05f);
	Countdown rightClick = Countdown(0.2f);
	Countdown countdownTurretSpawn = Countdown(1.0f);
	Countdown countdownCameraLock = Countdown(0.5f);
	Countdown infoscreen = Countdown(0.5f);
	Countdown KillMessage = Countdown(0.3f);
	Countdown CountdownSniperRifle = Countdown(1.0f);
	Player player = Player(100);
	
	
	//Turret Position
	Vector3 TurretPos;
	//Rock resource
	int resourceOfRock;
	//Gun
	bool isZoom = false;
	bool isSniper = false;
	//Flag
	bool isCapturing = false;
	bool isCaptured = false;
	//After killing aliens
	int Alienresources;

	//info screen
	bool isShown = false;

	// Astronaut UI menu stuff
	enum AstronautOptions
	{
		OPT_UP_PISTOL,
		OPT_UP_RIFLE,
		OPT_BACK_TO_MAIN,
		NUM_OPTIONS
	};

	string AstronautOpt[NUM_OPTIONS];
	int AstroCursor = 0;
	Countdown debounceUI = Countdown(0.1f);

	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];

	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	bool CameraMouseUpdate;
	Camera3 camera;

	MS modelStack, viewStack, projectionStack;

	Light light[2];
};

#endif