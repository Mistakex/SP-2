#include "Bullet.h"

Bullet::Bullet()
{
	position = Vector3(0, -10, 0);
}

Bullet::~Bullet()
{

}

Vector3 Bullet::getPosition()
{
	return position;
}

Vector3 Bullet::getView()
{
	return view;
}

void Bullet::updatePosition(const Vector3 &pos)
{
	position = pos;
}

void Bullet::setView(const Vector3 &view)
{
	this->view = view;
}

void Bullet::moveBullet(double dt,const float &speed)
{
	position += view * speed * dt;
	if (position.x > 500 || position.y > 500 || position.z > 500
		|| position.x < -500 || position.y < -500 || position.z < -500)
	{
		view = Vector3(0, 0, 0);
	}
}