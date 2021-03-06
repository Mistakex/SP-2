/******************************************************************************/
/*!
\file	Camera3.h
\author Cheng Zi Wei Keith
\par	email: 152639K\@mymail.nyp.edu.sg
\brief
Player camera colliding with objects and movement of camera
*/
/******************************************************************************/

#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "CountDown.h"
#include "Camera.h"
#include "Application.h"
#include <vector>
#include "Rock.h"
#include "Flag.h"
#include "CollisionObject.h"

using std::vector;

/******************************************************************************/
/*!
Class Camera3:
\brief
Holds all the variables for the movement of camera
*/
/******************************************************************************/

class Camera3 : public Camera
{
public:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 view;
	Vector3 right;

	float rotationX, rotationY;
	float MouseSensitivity;
	Camera3();
	~Camera3();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up,vector<Rock> *Rocks,Flag *flag,vector<CollisionObject> *Pillars);
	virtual void Update(double dt,int gameState);
	virtual void Reset();
	void CameraRotation(float CAMERASPEED);
	void JetPack(const double &dt);
	bool checkCollision(const Vector3 &center, const Vector3 &range, float moveX, float moveY);
	bool checkCircleCollision(Vector3 center, float range, float moveX, float moveY);
	bool checkReverseCircleCollision(Vector3 center, float range, float moveX, float moveY);
	bool checkRockCollision(float moveX, float moveZ);
	bool checkPillarCollision(float moveX, float moveZ);
	Countdown debounce = Countdown(0.5f);
	bool isFlying;
	bool jetpackMode;
	bool isFlyingOn;
	bool OnControls;

	//For collisions
	vector<CollisionObject> *Pillars;
	vector<Rock> *Rocks;
	Flag *flag;
};

#endif