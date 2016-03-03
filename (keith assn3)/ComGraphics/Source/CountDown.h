/******************************************************************************/
/*!
\file	CountDown.h
\author Leong Jun Xiang
\par	email: 152907b\@mymail.nyp.edu.sg
\brief
CountDown class
*/
/******************************************************************************/
#ifndef COUNTDOWN_H
#define COUNTDOWN_H
/******************************************************************************/
/*!
Class Countdown:
\brief	Countdown timer
*/
/******************************************************************************/
class Countdown
{
public:
	Countdown(const float& time);
	~Countdown();
	float TimeCountDown(double dt);
	void resetTime();
	float GetTimeNow();
private:
	float Time;
	float countdown;
};



#endif // !COUNTDOWN_H
