/******************************************************************************/
/*!
\file	CountDown.cpp
\author Leong Jun Xiang
\par	email: 152907b@mymail.nyp.edu.sg
\brief
Grenade from flying till explosion
*/
/******************************************************************************/
#include "CountDown.h"
/******************************************************************************/
/*!
\brief	constructor for Countdown 

\param	Time
Time for countdown
*/
/******************************************************************************/
Countdown::Countdown(const float & time) :Time(time)
{
	countdown = Time;
}
/******************************************************************************/
/*!
\brief	Countdown the time

\param	dt
delta time
\return
return time now
*/
/******************************************************************************/
float Countdown::TimeCountDown(double dt)
{
	if (countdown > 0)
	{
		countdown -= dt;
	}
	return countdown;
}
/******************************************************************************/
/*!
\brief	reset the time back to the original
*/
/******************************************************************************/
void Countdown::resetTime()
{
	countdown = Time;
}
/******************************************************************************/
/*!
\brief	returns the time now
\return
return time now
*/
/******************************************************************************/
float Countdown::GetTimeNow()
{
	return countdown;
}
/******************************************************************************/
/*!
\brief	defult destructor for countdown
*/
/******************************************************************************/
Countdown::~Countdown()
{
}