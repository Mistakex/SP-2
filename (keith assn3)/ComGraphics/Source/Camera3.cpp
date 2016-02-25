#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

extern GLFWwindow* m_window;
extern bool moving;

Camera3::Camera3()
{
	OnControls = true;
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up,vector<Rock> *Rocks,Flag *flag)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	MouseSensitivity = 0.2;
	this->up = defaultUp = right.Cross(view).Normalized();
	this->Rocks = Rocks;
	this->flag = flag;
}

void Camera3::CameraRotation(float CAMERASPEED)
{
	int WIDTH, HEIGHT;
	
	glfwGetWindowSize(m_window, &WIDTH, &HEIGHT);


	POINT p;
	GetCursorPos(&p);
	SetCursorPos(WIDTH/2, HEIGHT/2);

	rotationY -= (p.x - (float)WIDTH / 2) / (1 / CAMERASPEED);
	rotationX -= (p.y - (float)HEIGHT / 2) / (1 / CAMERASPEED);

	if (rotationX > 80.f)
	{
		rotationX = 80.f;
	}
	else if (rotationX < -80.f)
	{
		rotationX = -80.f;
	}

	if (rotationY >= 360.f || rotationY <= -360.f)
	{
		rotationY = 0.f;
	}

	target = Vector3(
		cos(Math::DegreeToRadian(rotationX)) * cos(Math::DegreeToRadian(rotationY)) + this->position.x,
		sin(Math::DegreeToRadian(rotationX)) + this->position.y,
		-(cos(Math::DegreeToRadian(rotationX)) * sin(Math::DegreeToRadian(rotationY))) + this->position.z
		);
}

static bool JUMPING = false; // is the character jumping?
static bool JUMPING_UP = true; // is the character in the middle of jumping?
static float JUMP_SPEED = 10.f; // speed of jump

bool Camera3::checkCollision(const Vector3 &center, const Vector3 &range,float moveX,float moveZ) // used to check collision for objects
{
	if (moveX > center.x - range.x && moveX < center.x + range.x
		&& moveZ > center.z - range.z && moveZ < center.z + range.z
		&& position.y > center.y - range.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Camera3::checkCircleCollision(Vector3 center,float range,float moveX, float moveZ) // used to check collision for objects
{
	if (sqrt(pow(moveX - center.x, 2) + pow(moveZ - center.z, 2)) < range)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Camera3::checkReverseCircleCollision(Vector3 center, float range, float moveX, float moveZ) // used to check collision for objects
{
	if (sqrt(pow(moveX - center.x, 2) + pow(moveZ - center.z, 2)) > range)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Camera3::checkAllCollision(float moveX, float moveZ) // used to check collision for objects
{
	for (vector<Rock>::iterator it = Rocks->begin(); it != Rocks->end(); ++it)
	{
		if (checkCollision(it->position, it->rangexyz, moveX, moveZ))
		{
			return true;
		}
	}
	return false;
}



void Camera3::Update(double dt,int gameState)
{
	if (OnControls)
	{
		static const float WALKSPEED = 5.f; // walkspeed
		static const float CAMERA_SPEED = 50.f;

		debounce.TimeCountDown(dt);
		if (Application::IsKeyPressed('O') && isFlyingOn == false && debounce.TimeCountDown(dt) < 0)
		{
			debounce.resetTime();
			isFlyingOn = true;
		}
		if (Application::IsKeyPressed('O') && isFlyingOn == true && debounce.TimeCountDown(dt) < 0)
		{
			debounce.resetTime();
			isFlyingOn = false;
		}

		if (isFlyingOn == false)
		{
			if (JUMPING == false)
			{
				if (position.y > 0.f)
				{
					position.y -= 10.f * dt;
				}
				else
				{
					position.y = 0.f;
				}
			}
			if (JUMPING == true)
			{
				if (JUMPING_UP == true && JUMP_SPEED > 0.f)
				{
					position += Vector3(0.f, JUMP_SPEED * dt, 0.f);
					JUMP_SPEED -= 10 * dt;
					if (JUMP_SPEED <= 0.f)
					{
						JUMPING_UP = false;
					}
				}
				if (JUMPING_UP == false && JUMP_SPEED < 10.f)
				{
					position -= Vector3(0.f, JUMP_SPEED * dt, 0.f);
					JUMP_SPEED += 10 * dt;
					if (JUMP_SPEED >= 10.f)
					{
						JUMPING_UP = true;
						JUMPING = false;
					}
				}
				if (position.y < 0.f)
				{
					position.y = 0.f;
				}
			}
		}

		if (isFlyingOn == true)
		{
			if (GetAsyncKeyState(' '))
			{
				isFlying = true;
			}
			else
			{
				isFlying = false;
			}

			if (isFlying == true)
			{
				position += Vector3(0.f, 5.5 * dt, 0.f);
				JUMPING_UP = true;
				if (position.y >= 50.f)
				{
					position -= Vector3(0.f, 7 * dt, 0.f);
				}
				if (position.y < 0.f)
				{
					position.y = 0.f;
					JUMPING_UP = false;
				}
			}
			else if (isFlying == false)
			{
				position -= Vector3(0.f, 7 * dt, 0.f);
				if (position.y < 0.f)
				{
					position.y = 0.f;
				}
			}
		}

		//movement keys are now geood
		if (Application::IsKeyPressed('A') || Application::IsKeyPressed('D') || Application::IsKeyPressed('W') || Application::IsKeyPressed('S'))
		{
			float moveX = 0, moveZ = 0;
			if (Application::IsKeyPressed('A'))
			{
				moveX += -right.x*(WALKSPEED)*dt;
				moveZ += -right.z*(WALKSPEED)*dt;

			}
			if (Application::IsKeyPressed('D'))
			{
				moveX += right.x*(WALKSPEED)*dt;
				moveZ += right.z*(WALKSPEED)*dt;

			}
			if (Application::IsKeyPressed('W'))
			{
				view = (Vector3(target.x, 0.f, target.z) - Vector3(position.x, 0.f, position.z)).Normalized();
				moveX += view.x*(WALKSPEED)*dt;
				moveZ += view.z*(WALKSPEED)*dt;

			}
			if (Application::IsKeyPressed('S'))
			{
				view = (Vector3(target.x, 0.f, target.z) - Vector3(position.x, 0.f, position.z)).Normalized();
				moveX += -view.x*(WALKSPEED)*dt;
				moveZ += -view.z*(WALKSPEED)*dt;

			}
			if (gameState == 0 || gameState == 1)
			{
				if (!checkAllCollision(moveX + position.x, position.z) && !checkCircleCollision(flag->position, 1.f, moveX + position.x, position.z))
				{
					position.x += moveX;
				}
				if (!checkAllCollision(position.x, moveZ + position.z) && !checkCircleCollision(flag->position, 1.f, position.x, moveZ + position.z))
				{
					position.z += moveZ;
				}
			}
			else if (gameState == 2)
			{
				if (!checkAllCollision(moveX + position.x, position.z) && !checkCircleCollision(Vector3(0,0,0), 18.5f, moveX + position.x, position.z))
				{
					position.x += moveX;
				}
				if (!checkAllCollision(position.x, moveZ + position.z) && !checkCircleCollision(Vector3(0, 0, 0), 18.5f, position.x, moveZ + position.z))
				{
					position.z += moveZ;
				}
			}
			else if (gameState == 3)
			{
				if (!checkAllCollision(moveX + position.x, position.z) && !checkReverseCircleCollision(Vector3(0, 0, 0), 69.f, moveX + position.x, position.z))
				{
					position.x += moveX;
				}
				if (!checkAllCollision(position.x, moveZ + position.z) && !checkReverseCircleCollision(Vector3(0, 0, 0), 69.f, position.x, moveZ + position.z))
				{
					position.z += moveZ;
				}
			}
		}
		if (Application::IsKeyPressed(' '))
		{
			if (JUMPING == false && position.y <= 0.f)
			{
				JUMPING = true;
			}
		}

		// boundaries
		float bounds = 100.f;

		if (position.x < -bounds)
		{
			position.x = -bounds;
		}
		else if (position.x > bounds)
		{
			position.x = bounds;
		}

		if (position.z < -bounds)
		{
			position.z = -bounds;
		}
		else if (position.z > bounds)
		{
			position.z = bounds;
		}

		//reset
		if (Application::IsKeyPressed('R'))
		{
			Reset();
		}

		//mouse rotation of camera
		CameraRotation(MouseSensitivity);

		view = (target - position).Normalized();
		right = view.Cross(defaultUp);
		right.y = 0;
		right.Normalize();
		this->up = right.Cross(view).Normalized();
	}
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	rotationX = 0;
	rotationY = 0;
	view = (target - position).Normalized();
	right = view.Cross(up);
	right.y = 0;
	right.Normalize();
}