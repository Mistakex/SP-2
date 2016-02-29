#ifndef MEDKIT_H
#define MEDKIT_H
#include "Player.h"
#include "CountDown.h"

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
private:

};


#endif // !MEDKIT_H
