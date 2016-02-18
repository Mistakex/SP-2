#ifndef BULLET_H
#define BULLET_H

#include "Vector3.h"

class Bullet
{
public:
	Bullet();
	~Bullet();
	Vector3 getPosition();
	void updatePosition(const Vector3 &pos);
	void setView(const Vector3 &view);
	void moveBullet(double dt);
private:
	Vector3 position;
	Vector3 view;
};


#endif