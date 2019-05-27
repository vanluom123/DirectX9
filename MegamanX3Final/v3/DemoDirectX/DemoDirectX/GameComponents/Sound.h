#pragma once
#include "dsound.h"
#include "windows.h"
#include <map>
#include <string>
#include <iostream>
#include <mmsystem.h>
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

class Sound
{
public:
	struct WaveHeaderStruct
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};

	~Sound();
	static Sound* GetInstance();

	void static Create(HWND hWnd);
	void SetVolume(float percentage, const std::string& name = "");
	void LoadSound(char* fileName, const std::string& name);
	void Play(const std::string& name, bool infiniteLoop, int times);
	void Stop(const std::string& name = "");
	bool IsPlaying(const std::string& name);

	float GetVolume() const;
	void Mute();
	void UnMute();
	void CleanUp() const;

private:
	Sound(HWND hWnd);
	static Sound* m_instance;

	IDirectSound8* m_device;
	IDirectSoundBuffer* m_primaryBuffer;
	std::map<std::string, IDirectSoundBuffer8*> m_soundBufferMap;
	bool m_isMute;

	float m_volume;

};