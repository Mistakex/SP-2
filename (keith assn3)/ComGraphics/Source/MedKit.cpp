#include "MedKit.h"

Medkit::Medkit(int maxhp, int healing, int timesHealed, const float recoverydelay, const float usagedelay)
	:HealTime(recoverydelay), CoolDown(usagedelay), initialHealingAmount(healing), initialTicks(timesHealed)
{
	activated = false;
	PlayerMaxHp = maxhp;
	HealAmount = healing;
	this->TimesHealed = timesHealed;
	MaxTimesHealed = timesHealed;
}
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
void Medkit::Activated()
{
	if (activated == true && CoolDown.GetTimeNow()<=0)
	{
		CoolDown.resetTime();
	}
}
void Medkit::TimerUpdate(double dt)
{
	CoolDown.TimeCountDown(dt);
	if (activated == true){ HealTime.TimeCountDown(dt); }
}
void Medkit::UpgradeHealing(int newHealAmount)
{
	HealAmount = newHealAmount;
}
Medkit::~Medkit()
{
}