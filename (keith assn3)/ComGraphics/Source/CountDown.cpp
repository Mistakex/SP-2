#include "CountDown.h"


Countdown::Countdown(const float & time) :Time(time)
{
	countdown = Time;
}
float Countdown::TimeCountDown(double dt)
{
	if (countdown > 0)
	{
		countdown -= dt;
	}
	else
	{
		countdown = Time;
	}

}
Countdown::~Countdown()
{
}