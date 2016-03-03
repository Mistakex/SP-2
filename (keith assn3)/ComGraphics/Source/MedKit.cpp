/******************************************************************************/
/*!
\file	Medkit.cpp
\author Leong Jun Xiang
\par	email: 152907b\@mymail.nyp.edu.sg
\brief
Medkit updates
*/
/******************************************************************************/
#include "MedKit.h"
/******************************************************************************/
/*!
\brief	constructor for Medkit
\param	maxhp
Max health value
\param	healing
healing value
\param	timesHealed
amount of ticks healed value
\param	recoverydelay
Delay between each tick value
\param	usagedelay
Delay between each use value
*/
/******************************************************************************/
Medkit::Medkit(int maxhp, int healing, int timesHealed, const float recoverydelay, const float usagedelay) :HealTime(recoverydelay), CoolDown(usagedelay), initialHealingAmount(healing), initialTicks(timesHealed)
{
	activated = false;
	PlayerMaxHp = maxhp;
	HealAmount = healing;
	this->TimesHealed = timesHealed;
	MaxTimesHealed = timesHealed;
}
/******************************************************************************/
/*!
\brief	increase health of player

\param	player
player object
*/
/******************************************************************************/
void Medkit::Heal(Player& player)
{
	if (activated == true)
	{
		if (HealTime.GetTimeNow() <= 0)
		{
			TimesHealed--;
			player.RecoverHp(HealAmount);
			HealTime.resetTime();
		}
		if (player.GetHp() > PlayerMaxHp)
		{
			player.RecoverHp(PlayerMaxHp - player.GetHp());
		}
		if (TimesHealed <= 0)
		{
			activated = false;
			TimesHealed = MaxTimesHealed;
		}
	}
}
/******************************************************************************/
/*!
\brief	reset cooldown when activated
*/
/******************************************************************************/
void Medkit::Activated()
{
	if (activated == true && CoolDown.GetTimeNow()<=0)
	{
		CoolDown.resetTime();
	}
}
/******************************************************************************/
/*!
\brief	updates the timer

\param	dt
delta time value
*/
/******************************************************************************/
void Medkit::TimerUpdate(double dt)
{
	CoolDown.TimeCountDown(dt);
	if (activated == true){ HealTime.TimeCountDown(dt); }
}
/******************************************************************************/
/*!
\brief	incrase the heal amount per tick

\param	newHealAmount
new heal amount
*/
/******************************************************************************/
void Medkit::UpgradeHealing(int newHealAmount)
{
	HealAmount = newHealAmount;
}
/******************************************************************************/
/*!
\brief	destructor for medkit
*/
/******************************************************************************/
Medkit::~Medkit()
{
}