#include <iostream>
#include <cstdlib>
#include <string>
#include <windows.h>

#include "Music.h"

using namespace irrklang;
using std::cout;
using std::endl;

Music::Music()
{
	soundEngine = createIrrKlangDevice();

	currentSound = 0;

	if (!soundEngine)
	{
		cout << "Error: Could not create sound engine" << endl;
		exit(0);
	}
	fileName = "\0";
	volume = 50;
	position = 0;
	soundEngine->setSoundVolume(1);

}

Music::Music(string soundFile)
{
	soundEngine = createIrrKlangDevice();
	currentSound = 0;

	if (!soundEngine)
	{
		cout << "Error: Could not create sound engine" << endl;
		exit(0);
	}

	fileName = soundFile;
	volume = 50;
	position = 0;
	soundEngine->setSoundVolume(1);
}

Music::~Music()
{
	soundEngine->drop();
	//currentSound->drop();
}

void Music::playSound()
{
	if (fileName == "\0")
	{
		cout << "Error: No sound file selected" << endl;
		return;
	}

	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);

	if (!currentSound)
	{
		cout << "Error: Could not play file" << endl;
		exit(0);
	}

	while (!currentSound->isFinished())
		Sleep(100);

	position = currentSound->getPlayPosition();
}

void Music::playSound(int milliseconds)
{
	if (fileName == "\0")
	{
		cout << "Error: No sound file selected" << endl;
		return;
	}

	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);

	if (!currentSound)
	{
		cout << "Error: Could not play file" << endl;
		exit(0);
	}

	Sleep(milliseconds);

	pause();
}

void Music::playSound(string soundFile)
{
	ISoundEngine* engine = createIrrKlangDevice();

	if (!engine) {
		cout << "Could not startup engine" << endl;
	}

	setFileName(soundFile);

	currentSound = engine->play2D(fileName.c_str(), false);
}

void Music::playSound(string soundFile, int milliseconds)
{
	setFileName(soundFile);

	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);

	if (!currentSound)
	{
		cout << "Error: Could not play file" << endl;
		exit(0);
	}

	Sleep(milliseconds);
	pause();
}

void Music::playSoundThreaded(string soundFile)
{
	setFileName(soundFile);

	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);
	if (!currentSound)
	{
		cout << "Error: Could not play file" << endl;
		exit(0);
	}
}

bool Music::isSoundPlaying()
{
	return !currentSound->isFinished();
}

void Music::pause()
{
	position = currentSound->getPlayPosition();
	soundEngine->setAllSoundsPaused();
}

void Music::resume()
{
	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);

	if (position != -1)
		currentSound->setPlayPosition(position);
}

void Music::setFileName(string soundFile)
{
	if (soundFile != "")
		fileName = soundFile;
}

string Music::getFileName()
{
	return fileName;
}

void Music::setVolume(int newVolume)
{
	if (newVolume < 0 || newVolume > 100)
		volume = 50;
	else
		volume = newVolume;

	currentSound->setVolume(volume / 100.0);
}

void Music::increaseVolume()
{
	volume += 10;

	if (volume > 100)
		volume = 100;
	currentSound->setVolume(volume / 100.0);
}

void Music::increaseVolume(int increment)
{
	volume += increment;

	if (volume > 100)
		volume = 100;
	currentSound->setVolume(volume / 100.0);
}

void Music::decreaseVolume()
{
	volume -= 10;

	if (volume < 0)
		volume = 0;
	currentSound->setVolume(volume / 100.0);
}

void Music::decreaseVolume(int increment)
{
	volume -= increment;

	if (volume < 0)
		volume = 0;
	currentSound->setVolume(volume / 100.0);
}

int Music::getCurrentVolume()
{
	return volume;
}
