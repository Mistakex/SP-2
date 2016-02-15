#include "Assignment3.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "LoadTGA.h"
#include "Utility.h"

#include <stdlib.h>

#include <sstream>

Assignment3::Assignment3()
{
}

Assignment3::~Assignment3()
{
}

void Assignment3::Init()
{
	
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

	light[0].type = Light::LIGHT_POINT;
	light[0].position.Set(0.f, 10.f, 20.f);
	light[0].color.Set(0, 0.5, 0);
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
	camera.Init(Vector3(0, 0, 0), Vector3(10,0,0), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 10, 20);

	meshList[GEO_SIGN] = MeshBuilder::GenerateCube("sign", Color(0.8, 0.8, 0.2));

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

	meshList[GEO_HELMET] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1));
	meshList[GEO_HELMET]->textureID = LoadTGA("Image//Helmet.tga");

	meshList[GEO_MODEL1] = MeshBuilder::GenerateOBJ("model", "OBJ//SpaceObject.obj");
	meshList[GEO_MODEL1]->textureID = LoadTGA("Image//outUV2.tga");

	meshList[GEO_MODEL2] = MeshBuilder::GenerateOBJ("Flag", "OBJ//flag.obj");
	meshList[GEO_MODEL2]->textureID = LoadTGA("Image//flagUV.tga");

	meshList[GEO_BOULDER] = MeshBuilder::GenerateOBJ("Boulder", "OBJ//boulder.obj");
	meshList[GEO_BOULDER]->textureID = LoadTGA("Image//boulder.tga");

	meshList[GEO_CRATER] = MeshBuilder::GenerateOBJ("crater", "OBJ//crater.obj");
	meshList[GEO_CRATER]->textureID = LoadTGA("Image//crater.tga");

	meshList[GEO_ALIENHEAD] = MeshBuilder::GenerateOBJ("alienhead", "OBJ//alienhead.obj");
	meshList[GEO_ALIENHEAD]->textureID = LoadTGA("Image//ALIENHEAD.tga");

	meshList[GEO_ALIENPART] = MeshBuilder::GenerateOBJ("alienpart", "OBJ//alienpart.obj");
	meshList[GEO_ALIENPART]->textureID = LoadTGA("Image//ALIENBODY.tga");

	meshList[GEO_ALIENBODY] = MeshBuilder::GenerateOBJ("alienbody", "OBJ//alienbody.obj");
	meshList[GEO_ALIENBODY]->textureID = LoadTGA("Image//ALIENBODY.tga");

	meshList[GEO_TENT] = MeshBuilder::GenerateOBJ("alienbody", "OBJ//moonbase.obj");
	meshList[GEO_TENT]->textureID = LoadTGA("Image//spacetent.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	Mtx44 projection;
	projection.SetToPerspective(70.0f, 4.0f / 3.0f, 0.1f, 5000.0f);
	projectionStack.LoadMatrix(projection);
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

static float LSPEED = 10.f; // LIGHT SPEED

//***************CREATE A CLASS WITH THESE VALUES FOR A PLAYER CLASS**************//
bool moving = false; // Is player moving
static bool movingUP = true; // is the helmet moving up
static float helmetY = 0.f; // Y-coordinates of helmet
static bool retractedHelmet = false; // is the helmet retracted
static float helmetUP = 0.f; // moving the helmet up when retracted
static float helmetDebounce = 0.f; // debounce of helmet
static bool displayMore = false;
//***********************************************************************//

//****************CREATE FOR FLAG CLASS********************************//
static float flagRotate = 0.f; // rotation of flag
static bool flagDropped = false; // has the flag started dropping
static bool flagHasDropped = false; // check if flag has finish dropping
static bool flagDropFront = true; // which side the flag is dropping towards
static Vector3 FLAG(5, -1, 0); // coordinates of flag
//********************************************************************//

//********************ENEMY CLASS***********************************//
static float alienArmRotate = 0.f; // rotation of alien arms
static float alienY = 0.f; // Y-coordinate of aliens
static float alienJumping = true; // are the aliens jumping
//******************************************************************//

Vector3 SHIP(20, 0, 0); // coordinates of SHIP
static float shipNotiSize = 1.f; // notification size of the Press 'E' 
static bool shipFlew = false; // has the ship flown

static float skyBoxRotate = 0.f; // rotation of skybox

static std::stringstream framerate;

static Vector3 frontPush; // direction of push infront of flag


void Assignment3::Update(double dt)
{
	camera.Update(dt);

	// updating 2nd light
	light[1].position.Set(camera.position.x + camera.target.x/15,
		camera.position.y + camera.target.y/15 + helmetY * 10 + helmetUP,
		camera.position.z + camera.target.z/15);
	light[1].spotDirection.Set(-(camera.target.x - camera.position.x), -(camera.target.y - camera.position.y), -(camera.target.z - camera.position.z));

	//first light
	light[0].position.Set(0.f, 5.f + alienY, 20.f);

	//debounce of helmet
	helmetDebounce += 1.f * dt;

	//framerate
	framerate << "Framerate:" << 1 / dt;

	//aliens only dance when flag has dropped
	if (flagHasDropped == true)
	{
		if (alienJumping == true)
		{
			alienArmRotate += 360.f * dt;
			alienY += 0.5*dt;
			if (alienArmRotate >= 180.f)
			{
				alienJumping = false;
			}
		}
		else if (alienJumping == false)
		{
			alienArmRotate -= 360.f * dt;
			alienY -= 0.5*dt;
			if (alienArmRotate <= 0.f)
			{
				alienY = 0.f;
				alienArmRotate = 0.f;
				alienJumping = true;
			}
		}
	}
	else
	{
		alienArmRotate = 0.f; 
		alienY = 0.f; 
		alienJumping = true;
	}

	//rotation of skybox
	if (skyBoxRotate < 360.f)
	{
		skyBoxRotate += (float)dt;
	}
	else
	{
		skyBoxRotate = 0.f;
	}

	// helmet retraction code
	if (retractedHelmet == true)
	{
		if (helmetUP < 1.f)
		{
			helmetUP += 0.6*dt;
		}
	}
	else if (retractedHelmet == false)
	{
		if (helmetUP > 0.f)
		{
			helmetUP -= 0.6*dt;
		}
		else
		{
			helmetUP = 0.f;
		}
	}

	// moving up and down of helmet
	if (moving == true)
	{
		if (movingUP == true)
		{
			helmetY += 0.1 * dt;
			if (helmetY >= 0.01)
			{
				movingUP = false;
			}
		}
		else if (movingUP == false)
		{
			helmetY -= 0.1 * dt;
			if (helmetY <= -0.01)
			{
				movingUP = true;
				moving = false;
			}
		}
	}
	else if (moving == false)
	{
		if (helmetY > 0.f)
		{
			helmetY -= 0.1 * dt;
			if (helmetY < 0.f)
				helmetY = 0.f;
		}
		else if (helmetY < 0.f)
		{
			helmetY += 0.1 * dt;
			if (helmetY > 0.f)
				helmetY = 0.f;
		}
	}
	
	// flag drop direction
	if (flagDropped == false
		&& camera.position.x >= FLAG.x - 1.f && camera.position.x <= FLAG.x + 1.f
		&& camera.position.y < 2.f
		&& camera.position.z >= FLAG.z - 1.f && camera.position.z <= FLAG.z + 1.f)
	{
		frontPush = (Vector3(camera.target.x, 0.f, camera.target.z) - Vector3(camera.position.x, 0.f, camera.position.z)).Normalized();
		flagDropped = true;
		if (camera.position.x <= FLAG.x)
		{
			flagDropFront = false;
		}
	}

	// flag dropping to side
	if (flagDropped == true && flagHasDropped == false)
	{
		
		if (flagDropFront == false)
		{
			flagRotate += 90.f * dt;
			FLAG += frontPush * (float)(5.f * dt);
			if (flagRotate > 90.f)
			{
				flagRotate = 90.f;
				flagHasDropped = true;
			}
		}
		else if (flagDropFront == true)
		{
			flagRotate -= 90.f * dt;
			FLAG += frontPush * (float)(5.f * dt);
			if (flagRotate < -90.f)
			{
				flagRotate = -90.f;
				flagHasDropped = true;
			}
		}
	}

	// the ship has flown
	if (shipFlew == true)
	{
		if (SHIP.y < 5.f)
			SHIP += Vector3(-1, 1, 0) * dt;
		else if (SHIP.x < -5000)
			shipFlew = false;
		else
			SHIP += Vector3(-20, 1, 0) * dt;
	}

	// backface culling
	if (Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	// taking off helmet
	if (Application::IsKeyPressed('F'))
	{
		if (retractedHelmet == false && helmetDebounce > 0.3f)
		{
			retractedHelmet = true;
			helmetDebounce = 0.f;
		}
		else if (retractedHelmet == true && helmetDebounce > 0.3f)
		{
			retractedHelmet = false;
			helmetDebounce = 0.f;
		}
	}

	// display more info
	if (Application::IsKeyPressed('U'))
	{
		if (displayMore == false && helmetDebounce > 0.3f)
		{
			displayMore = true;
			helmetDebounce = 0.f;
		}
		else if (displayMore == true && helmetDebounce > 0.3f)
		{
			displayMore = false;
			helmetDebounce = 0.f;
		}
	}

	//reset everything
	if (Application::IsKeyPressed('R'))
	{
		flagRotate = 0.f;
		flagDropped = false;
		flagHasDropped = false;
		flagDropFront = true;
		FLAG = Vector3(5,-1,0);

		SHIP = Vector3(20, 0, 0);
		shipFlew = false;

		retractedHelmet = false;
	}

	// interact with ship
	if (Application::IsKeyPressed('E'))
	{
		if (camera.position.x > SHIP.x - 6.f && camera.position.x < SHIP.x + 6.f
			&& camera.position.z > SHIP.z - 6.f && camera.position.z < SHIP.z + 6.f
			&& shipFlew == false)
		{
			shipFlew = true;
		}
	}
	if (camera.position.x > SHIP.x - 6.f && camera.position.x < SHIP.x + 6.f
		&& camera.position.z > SHIP.z - 6.f && camera.position.z < SHIP.z + 6.f
		&& shipFlew == false)
	{
		if (shipNotiSize < 6.0f)
		{
			shipNotiSize += 10.f * dt;
		}
	}
	else
	{
		shipNotiSize = 1.f;
	}
	
	//checking collisions
	checkCollision(SHIP, 4.f, 4.f, 3.f);
	checkCollision(Vector3(9, 0, -20), 5.f, 1.f, 3.f);


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



//*****************UPDATE ADD NEW OVERLOAD FOR POSITION OF PLAYER AND BULLET*****************//
void Assignment3::checkCollision(const Vector3 &center, float x1, float z1, float y1) // used to check collision for objects
{
	if (camera.position.x > center.x - x1 && camera.position.x < center.x + x1
		&& camera.position.z > center.z - z1 && camera.position.z < center.z + z1
		&& camera.position.y > center.y - y1)
	{
		if (camera.position.x < center.x + x1 && camera.position.x > center.x + (x1 - 0.3f))
		{
			camera.position.x = center.x + x1;
		}
		if (camera.position.x > center.x - x1 && camera.position.x < center.x - (x1 - 0.3f))
		{
			camera.position.x = center.x - x1;
		}
		if (camera.position.z < center.z + z1 && camera.position.z > center.z + (z1 - 0.3f))
		{
			camera.position.z = center.z + z1;
		}
		if (camera.position.z > center.z - z1 && camera.position.z < center.z - (z1 - 0.3f))
		{
			camera.position.z = center.z - z1;
		}
	}
}
//******************************************************************************************************//
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
		characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
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
		characterSpacing.SetToTranslation(i * 0.8f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
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

void Assignment3::RenderModelOnScreen(Mesh *mesh, bool enableLight, float size, float x, float y) // used to render helmet on screen
{

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
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Rotate(90, 1, 0, 0);
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
	//RenderMesh(meshList[GEO_AXES], false);

	//floor
	modelStack.PushMatrix();
	modelStack.Translate(0, -1, 0);
	modelStack.Scale(100, 1, 100);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	//SHIP
	modelStack.PushMatrix();
	modelStack.Translate(SHIP.x,SHIP.y,SHIP.z);
	modelStack.Rotate(4, 0, 0, 1);
	modelStack.Translate(0, -1, 0);
	RenderMesh(meshList[GEO_MODEL1], true);
	modelStack.PopMatrix();
	
	//FLAG
	modelStack.PushMatrix();
	modelStack.Translate(FLAG.x,FLAG.y,FLAG.z);
	modelStack.Rotate(-flagRotate, 0, 0, 1);
	modelStack.Rotate(90, 0, 1, 0);
	RenderMesh(meshList[GEO_MODEL2], true);
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
				modelStack.Translate(-20, -0.5, 10 - j*20);
				modelStack.Scale(3, 2, 3);
				RenderMesh(meshList[GEO_CRATER], true);
				modelStack.PopMatrix();
			}
		}
	}

	// ROCKS AT PERIMETER
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-50 + j * 10, 1, -50 + 100*i);
			modelStack.Scale(10, 5, 10);
			RenderMesh(meshList[GEO_BOULDER], true);
			modelStack.PopMatrix();
		}
	}
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-50 + i*100, 1, -50 + j * 10);
			modelStack.Scale(10, 5, 10);
			RenderMesh(meshList[GEO_BOULDER], true);
			modelStack.PopMatrix();
		}
	}

	//MOONBASE
	
	for (int j = 0; j < 3; ++j)
	{
		for (int i = -1; i < j; ++i)
		{
			modelStack.PushMatrix();
			modelStack.Translate(3 - i*10, -0.9, -25 - 7 * j);
			modelStack.Rotate(-135 + j*45 - i*45, 0, 1, 0);
			modelStack.Scale(1 + j*0.5, 1 + j*0.5, 1 + j*0.5);
			RenderMesh(meshList[GEO_TENT], true);
			modelStack.PopMatrix();
		}
	}
	modelStack.PushMatrix();
	modelStack.Translate(5, 0, -20);
	modelStack.PushMatrix();
	modelStack.Translate(4, 0, -0.5);
	modelStack.Scale(10, 2, 1);
	RenderMesh(meshList[GEO_SIGN], true);
	modelStack.PopMatrix();
	RenderText(meshList[GEO_TEXT], "MOON BASE", Color(1, 1, 0));
	modelStack.PopMatrix();

	// HELMET

	modelStack.PushMatrix();
	RenderModelOnScreen(meshList[GEO_HELMET], true, 120, 0.35, 0.2 + helmetY + helmetUP);
	RenderTextOnScreen(meshList[GEO_TEXT], framerate.str(), Color(0, 1, 1), 3, 1, 1 + helmetY * 40 + helmetUP * 40);
	RenderTextOnScreen(meshList[GEO_TEXT], "Push F to take off helmet", Color(0, 1, 1), 3, 1, 18.5 + helmetY * 40 + helmetUP * 40);
	if (displayMore == false)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "(Press 'U' to see more info)", Color(0, 1, 1), 2.5, 1, 20.5 + helmetY * 48 + helmetUP * 48);
	}
	else
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "UI only available with helmet on", Color(0, 1, 1), 2, 1, 20.5 + helmetY * 60 + helmetUP * 60);
		RenderTextOnScreen(meshList[GEO_TEXT], "Some things can only be seen without the helmet", Color(1, 0, 0), 2, 1, 18.5 + helmetY * 60 + helmetUP * 60);
		RenderTextOnScreen(meshList[GEO_TEXT], "The flag may be scaring extraterrestial life!", Color(0, 1, 0), 2, 1, 16.5 + helmetY * 60 + helmetUP * 60);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'R' to reset", Color(0, 1, 1), 2, 1, 14.5 + helmetY * 60 + helmetUP * 60);
	}
	RenderTextOnScreen(meshList[GEO_TEXT], "PD ENTERTAINMENT INC.", Color(0, 1, 0), 2, 1, -15 + helmetY * 60 + helmetUP * 60);
	if (camera.position.x > SHIP.x - 6.f && camera.position.x < SHIP.x + 6.f
		&& camera.position.z > SHIP.z - 6.f && camera.position.z < SHIP.z + 6.f
		&& shipFlew == false)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press 'E'", Color(0, 1, 0), shipNotiSize, 3, 5 + helmetY * 20 + helmetUP * 20);
	}

	framerate.str("");
	modelStack.PopMatrix();

	//ALIEN

	for (int j = 0; j < 6; ++j)
	{
		for (int i = -1 - j; i < 2 + j; ++i)
		{
			modelStack.PushMatrix();
			modelStack.Translate(i* -3, alienY, 5 + j * 5);
			modelStack.Rotate(0, 0, 0, 1);
			RenderAlien();
			modelStack.PopMatrix();
		}
	}
	
}

void Assignment3::RenderAlien()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, -3.2, 0);
	RenderMesh(meshList[GEO_ALIENHEAD], true);
	RenderMesh(meshList[GEO_ALIENBODY], true);
	modelStack.PushMatrix();
	modelStack.Translate(0, 2.9, 0);
	modelStack.Rotate(alienArmRotate, 1, 0, 0);
	modelStack.Translate(0, -2.9, 0);
	modelStack.PushMatrix(); // arms
	modelStack.Translate(-0.3, 2.7, 0);
	modelStack.Scale(0.2, 0.4, 0.4);
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