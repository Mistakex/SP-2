/******************************************************************************/
/*!
\file	Music.cpp
\author Chin Hao Ming
\par	email: 154158D@mymail.nyp.edu.sg
\brief
Play music, pause, resume, increase and decrease volumes.
*/
/******************************************************************************/
#include <iostream>
#include <cstdlib>
#include <string>
#include <windows.h>

#include "Music.h"

using namespace irrklang;
using std::cout;
using std::endl;

/******************************************************************************/
/*!
\brief
Default constructor for music class
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
Constructor for music class

\param	soundFile
Location of sound file to be played
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
Default destructor for music class
*/
/******************************************************************************/
Music::~Music()
{
	soundEngine->drop();
	currentSound->drop();
}

/******************************************************************************/
/*!
\brief
Plays sound
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
Plays sound for an amount of time
\param milliseconds
Amount of time to play sound.
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
Plays sound by taking the location of the file
\param soundFile
Location of sound file
*/
/******************************************************************************/
void Music::playSound(string soundFile)
{
	ISoundEngine* engine = createIrrKlangDevice();

	if (!engine) {
		cout << "Could not startup engine" << endl;
	}

	setFileName(soundFile);

	currentSound = engine->play2D(fileName.c_str(), false);
}

/******************************************************************************/
/*!
\brief
Plays sound by taking the location of the file & for an amount of time
\param soundFile
Location of sound file
\param milliseconds
Amount of time to play sound
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
Plays sound by taking the location of the file while program is running
\param soundFile
Location of sound file
*/
/******************************************************************************/
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

/******************************************************************************/
/*!
\brief
Checks whether any sound is playing
\Return
Return whether sound has finish or still playing
*/
/******************************************************************************/
bool Music::isSoundPlaying()
{
	return !currentSound->isFinished();
}

/******************************************************************************/
/*!
\brief
Pauses the current sound
*/
/******************************************************************************/
void Music::pause()
{
	position = currentSound->getPlayPosition();
	soundEngine->setAllSoundsPaused();
}

/******************************************************************************/
/*!
\brief
Resumes the sound that was paused
*/
/******************************************************************************/
void Music::resume()
{
	currentSound = soundEngine->play2D(fileName.c_str(), false, false, true);

	if (position != -1)
		currentSound->setPlayPosition(position);
}

/******************************************************************************/
/*!
\brief
Sets the file name to soundFile
*/
/******************************************************************************/
void Music::setFileName(string soundFile)
{
	if (soundFile != "")
		fileName = soundFile;
}

/******************************************************************************/
/*!
\brief
Returns file name of sound
*/
/******************************************************************************/
string Music::getFileName()
{
	return fileName;
}

/******************************************************************************/
/*!
\brief
Sets sound voulume
\param newVolume
volume of sound
*/
/******************************************************************************/
void Music::setVolume(int newVolume)
{
	if (newVolume < 0 || newVolume > 100)
		volume = 50;
	else
		volume = newVolume;

	currentSound->setVolume(volume / 100.0);
}

/******************************************************************************/
/*!
\brief
Increases the volume
*/
/******************************************************************************/
void Music::increaseVolume()
{
	volume += 10;

	if (volume > 100)
		volume = 100;
	currentSound->setVolume(volume / 100.0);
}

/******************************************************************************/
/*!
\brief
Increases the volume
\param increment
Increases the volume by a number.
*/
/******************************************************************************/
void Music::increaseVolume(int increment)
{
	volume += increment;

	if (volume > 100)
		volume = 100;
	currentSound->setVolume(volume / 100.0);
}

/******************************************************************************/
/*!
\brief
Decreases sound volume
*/
/******************************************************************************/
void Music::decreaseVolume()
{
	volume -= 10;

	if (volume < 0)
		volume = 0;
	currentSound->setVolume(volume / 100.0);
}

/******************************************************************************/
/*!
\brief
Decreases sound volume
\param increment
Decreases the volume by a number.
*/
/******************************************************************************/
void Music::decreaseVolume(int increment)
{
	volume -= increment;

	if (volume < 0)
		volume = 0;
	currentSound->setVolume(volume / 100.0);
}

/******************************************************************************/
/*!
\brief
Gets current volume of sound
\Return
Return volume
*/
/******************************************************************************/
int Music::getCurrentVolume()
{
	return volume;
}
