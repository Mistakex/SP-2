#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "CountDown.h"
#include "Camera.h"
#include "Application.h"

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
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();
	void CameraRotation(float CAMERASPEED);
	bool checkCollision(const Vector3 &center, const Vector3 &range, float moveX, float moveY);
	Countdown debounce = Countdown(0.5f);
	bool isFlying = false;
	bool jetpackMode = false;
	bool isFlyingOn = false;
};

#endif