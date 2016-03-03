/******************************************************************************/
/*!
\file	Enemy.cpp
\author Cheng Zi Wei Keith
\par	email: 152639K@mymail.nyp.edu.sg
\brief
Ship transitions and cutscenes.
*/
/******************************************************************************/
#include "Ship.h"

/******************************************************************************/
/*!
\brief
Default constructor for enemy class
\param pos
Ship position
\param range
Collision range of ship
*/
/******************************************************************************/
Ship::Ship(const Vector3 &pos,const Vector3 &range)
{
	position = pos;
	defaultPosition = pos;
	rangexyz = range;
	cutsceneTimer = 0.f;
	fadesize = 0.1f;
}

/******************************************************************************/
/*!
\brief
Default destructor for ship class
*/
/******************************************************************************/
Ship::~Ship()
{

}

/******************************************************************************/
/*!
\brief
Initialization of camera to ship
\param camera
Change camera to ship
*/
/******************************************************************************/
void Ship::init(Camera3 *camera)
{
	Camera = camera;
}

/******************************************************************************/
/*!
\brief
Cutscene for ship
\param dt
timer for cutscene
*/
/******************************************************************************/
void Ship::cutscene(const double &dt)
{
	if (updateCutscene)
	{
		Camera->OnControls = false;
		Camera->target = position;
		cutsceneTimer += (float)dt;
		if (cutsceneTimer < 2.f)
		{
			Camera->position = Vector3(0, 0, -35);
			position += Vector3(0, 3, 0)*(float)dt;
		}
		else if (cutsceneTimer < 4.f)
		{
			Camera->position = (position.x, 0, position.z);
			position += Vector3(0, 3, 0)*(float)dt;
		}
		else if (cutsceneTimer < 8.f)
		{
			Camera->position = position + Vector3(10, -3, 0);
			position -= Vector3(100, 0, 0)*(float)dt;
			if (cutsceneTimer > 6.f)
			{
				displayFade = true;
				fadesize += 100.f * (float)dt;
			}
		}
		else if (cutsceneTimer > 9.f)
		{
			Camera->OnControls = true;
			changeScene = true;
			Camera->position = Vector3(0, 0, 70);
			if (fadesize - 10.f*(float)dt > 0.f)
				fadesize -= 100.f * (float)dt;
			else
			{
				fadesize = 0.1f;
				displayFade = false;
				updateCutscene = false;
				cutsceneTimer = 0.f;
				changeScene = false;
				position = defaultPosition;
			}
		}
	}
}