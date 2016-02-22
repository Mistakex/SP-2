#include "Music.h"

std::wstring MusicFiles[] = {L"Music/mining.wav"};

void playMusic(int Music)
{
	PlaySound(MusicFiles[Music].c_str(), GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
}