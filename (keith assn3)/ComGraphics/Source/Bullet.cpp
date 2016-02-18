#include "Bullet.h"

Bullet::Bullet()
{
	position = Vector3(0, -10, 0);
}

Bullet::~Bullet()
{

}

void Bullet::updatePosition(const Vector3 &pos)
{
	position = pos;
}

void Bullet::setView(const Vector3 &view)
{
	this->view = view;
}

void Bullet::moveBullet(double dt)
{
	float speed = 100;
	position += view * speed * dt;
}