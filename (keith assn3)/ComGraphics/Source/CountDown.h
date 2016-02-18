#ifndef COUNTDOWN_H
#define COUNTDOWN_H

class Countdown
{
public:
	Countdown(const float& time);
	~Countdown();
	float TimeCountDown(double dt);
	void resetTime();
	float GetTimeNow();
private:
	const float Time;
	float countdown;
};



#endif // !COUNTDOWN_H
