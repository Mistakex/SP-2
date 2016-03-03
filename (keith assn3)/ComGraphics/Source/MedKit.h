/******************************************************************************/
/*!
\file	Medkit.h
\author Leong Jun Xiang
\par	email: 152907b@mymail.nyp.edu.sg
\brief
Medkit Functions
*/
/******************************************************************************/
#ifndef MEDKIT_H
#define MEDKIT_H
#include "Player.h"
#include "CountDown.h"
/******************************************************************************/
/*!
Class Medkit:
\brief	Medkit functions and stats
*/
/******************************************************************************/
class Medkit
{
public:
	Medkit(int maxhp,int healing,int times,const float recoverydelay,const float usagedelay);
	~Medkit();
	Countdown HealTime;
	Countdown CoolDown;

	void Heal(Player& player);
	void Activated();
	void UpgradeHealing(int);
	void TimerUpdate(double dt);
	bool activated;
	int MaxTimesHealed;
	int TimesHealed;
	int PlayerMaxHp;
	int HealAmount;
	const int initialTicks; // Base amount of times that it heals
	const int initialHealingAmount; // Base amount of health it heals
private:
};


#endif // !MEDKIT_H
