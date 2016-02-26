#ifndef _MUSIC_H
#define _MUSIC_H

#include <iostream>
#include <string>
#include <Windows.h>
#include <MMSystem.h>

#include "../include/irrKlang.h"
using namespace irrklang;
using std::string;
#pragma comment(lib, "../lib/Win32-visualStudio/irrKlang.lib")

class Music
{
private:
	ISoundEngine* soundEngine;
	ISound* currentSound;
	string fileName;
	int volume;
	int position;

public:
	Music();
	Music(string soundFile); // Doesn't play sound, only initializes fileName
	~Music();

	void playSound(); // Plays entire sound file
	void playSound(int milliseconds); // Plays for X number of milliseconds
	void playSound(string soundFile); // Play entire specified sound file
	void playSound(string soundFile, int milliseconds);
	void playSoundThreaded(string soundFile); // Starts playing sound but program continues
	bool isSoundPlaying(); // True = music is playing

	// Pause/Resume, works like any other media player
	void pause();
	void resume();

	// Set/get sound file to be played/playing
	void setFileName(string soundFile);
	string getFileName();

	// Volume controls
	void setVolume(int newVolume);
	void increaseVolume();
	void increaseVolume(int increment);
	void decreaseVolume();
	void decreaseVolume(int increment);
	int getCurrentVolume();

};

#endif