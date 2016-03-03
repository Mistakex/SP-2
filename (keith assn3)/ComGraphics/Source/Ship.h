/******************************************************************************/
/*!
\file	Enemy.h
\author Cheng Zi Wei Keith
\par	email: 152639K@mymail.nyp.edu.sg
\brief
Ship that is used for transition of scenes
*/
/******************************************************************************/

#ifndef SHIP_H
#define SHIP_H

#include "Camera3.h"
#include "GameObject.h"

/******************************************************************************/
/*!
Class Ship:
\brief	Ship status and functions It is a child of GameObject
*/
/******************************************************************************/
class Ship :public GameObject
{
public:
	Ship(const Vector3 &pos,const Vector3 &range);
	~Ship();
	void init(Camera3 *camera);
	void cutscene(const double &dt); // cutscene update function
	float fadesize; // size of cutscene fading
	bool displayFade; // whether or not to display the scene changer
	bool updateCutscene; // whether or not to update the cutscene
	bool changeScene; // is the scene changing?
private:
	Camera3 *Camera;
	float cutsceneTimer;
	Vector3 defaultPosition;
};


#endif