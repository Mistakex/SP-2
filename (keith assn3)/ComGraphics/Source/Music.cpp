#include "Music.h"

std::wstring MusicFiles[] = { L"Music/bgm.wav", L"Music/mining.wav", L"Music/bgm2.wav"};

void playMusic(int Music)
{
	PlaySound(MusicFiles[Music].c_str(), GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
}