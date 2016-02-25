#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "CountDown.h"
#include "Camera.h"
#include "Application.h"
#include <vector>
#include "Rock.h"
#include "Flag.h"

using std::vector;

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
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up,vector<Rock> *Rocks,Flag *flag);
	virtual void Update(double dt);
	virtual void Reset();
	void CameraRotation(float CAMERASPEED);
	bool checkCollision(const Vector3 &center, const Vector3 &range, float moveX, float moveY);
	bool checkFlagCollision(float moveX, float moveY);
	bool checkAllCollision(float moveX, float moveZ);
	Countdown debounce = Countdown(0.5f);
	bool isFlying;
	bool jetpackMode;
	bool isFlyingOn;
	bool OnControls;

	//For collisions
	vector<Rock> *Rocks;
	Flag *flag;
};

#endif