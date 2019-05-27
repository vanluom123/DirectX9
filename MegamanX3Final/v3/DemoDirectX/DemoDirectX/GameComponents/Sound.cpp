#include "Sound.h"
#include "GameGlobal.h"

Sound* Sound::m_instance = NULL;

Sound* Sound::GetInstance()
{
	if (m_instance == NULL)
		m_instance = new Sound(GameGlobal::GetHWND());

	return m_instance;
}

Sound::Sound(HWND hWnd)
{
	m_primaryBuffer = NULL;

	DSBUFFERDESC bufferDesc; //describe the buffer

	HRESULT result = DirectSoundCreate8(NULL, &m_device, NULL);
	if (result != S_OK)
		return;

	result = m_device->SetCooperativeLevel(hWnd, DSSCL_PRIORITY); // set the cooperative level.
	if (result != S_OK)
		return;

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	result = m_device->CreateSoundBuffer(&bufferDesc, &m_primaryBuffer, NULL);
	if (result != S_OK)
		return;

	m_volume = 75.0f;
	m_isMute = false;

	// -----------LOAD SOUND-----------

	// Blast hornet sound
	LoadSound("Resources/Sound/Blast Hornet.wav", "BlastHornet");

	// RockMan sound
	LoadSound("Resources/Sound/Shooting bullet.wav", "ShootingBullet");
	LoadSound("Resources/Sound/Absorb energy.wav", "AbsorbShortEnergy");
	LoadSound("Resources/Sound/Absorb long energy.wav", "AbsorbLongEnergy");
	LoadSound("Resources/Sound/Give up short energy.wav", "GiveUpShortEnergy");
	LoadSound("Resources/Sound/Give up long energy.wav", "GiveUpLongEnergy");
	LoadSound("Resources/Sound/Fall down ground.wav", "FallDownGround");
	LoadSound("Resources/Sound/Die.wav", "RockmanDie");
	LoadSound("Resources/Sound/jump.wav", "JumpUp");//Use to jump and to cling
	LoadSound("Resources/Sound/dash.wav", "dash");

	// Enemies explosion
	LoadSound("Resources/Sound/explosions.wav", "explosions");
}

Sound::~Sound()
{
	for (std::map<std::string, IDirectSoundBuffer8*>::iterator it = m_soundBufferMap.begin(); it != m_soundBufferMap.end(); ++it)
	{
		if (it->second)
		{
			it->second->Release();
			it->second = NULL;
		}
	}
	if (m_primaryBuffer)
		m_primaryBuffer->Release();
	if (m_device)
		m_device->Release();
	m_device = NULL;

	m_primaryBuffer = NULL;
}

void Sound::Create(HWND hWnd)
{
	if (m_instance == NULL)
		m_instance = new Sound(hWnd);
}

float Sound::GetVolume() const
{
	return m_volume;
}

void Sound::LoadSound(char* fileName, const std::string& name)
{
	if (m_soundBufferMap.find(name) != m_soundBufferMap.end())
		return;

	FILE* filePtr;
	WaveHeaderStruct waveHeaderStruct;
	IDirectSoundBuffer* tempBuffer;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;
	unsigned char* bufferPtr;
	unsigned long bufferSize;

	int error = fopen_s(&filePtr, fileName, "rb");
	if (error != 0)
		return;

	fread(&waveHeaderStruct, sizeof(WaveHeaderStruct), 1, filePtr);

	if ((waveHeaderStruct.format[0] != 'W') || (waveHeaderStruct.format[1] != 'A') ||
		(waveHeaderStruct.format[2] != 'V') || (waveHeaderStruct.format[3] != 'E'))
		return;

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = waveHeaderStruct.sampleRate;
	waveFormat.wBitsPerSample = waveHeaderStruct.bitsPerSample;
	waveFormat.nChannels = waveHeaderStruct.numChannels;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	bufferDesc.dwBufferBytes = waveHeaderStruct.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	IDirectSoundBuffer8* secondaryBuffer = NULL;
	IDirectSoundBuffer8** pSecondaryBuffer = &secondaryBuffer;

	m_device->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);

	long result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, reinterpret_cast<void**>(&(*pSecondaryBuffer)));

	tempBuffer->Release();
	tempBuffer = NULL;

	if (FAILED(result))
		return;

	fseek(filePtr, sizeof(WaveHeaderStruct), SEEK_SET);


	auto* wavData = new unsigned char[ waveHeaderStruct.dataSize];


	fread(wavData, waveHeaderStruct.dataSize, 1, filePtr);

	error = fclose(filePtr);
	if (error != 0)
		return;

	result = (*pSecondaryBuffer)->Lock(0, waveHeaderStruct.dataSize, reinterpret_cast<void**>(&bufferPtr), static_cast<DWORD*>(&bufferSize), NULL, NULL, 0);

	if (FAILED(result))
		return;

	memcpy(bufferPtr, wavData, waveHeaderStruct.dataSize);

	(*pSecondaryBuffer)->Unlock(static_cast<void*>(bufferPtr), bufferSize, NULL, 0);

	if (wavData != NULL)
	{
		delete[] wavData; 
		wavData = NULL;
	}

	long tempVolume = (m_volume) / 100 * (- DSBVOLUME_MIN) + DSBVOLUME_MIN;
	(*pSecondaryBuffer)->SetVolume(tempVolume);

	m_soundBufferMap[name] = secondaryBuffer;
}

void Sound::Play(const std::string& name, bool infiniteLoop, int times)
{
	if (m_isMute == true || IsPlaying(name) == true)
		return;

	std::map<std::string, IDirectSoundBuffer8*>::iterator it;
	it = m_soundBufferMap.find(name);
	if (it == m_soundBufferMap.end())
		return;
	if (infiniteLoop == true)
		it->second->Play(0, 0, DSBPLAY_LOOPING);
	else
	{
		it->second->Stop();
		it->second->SetCurrentPosition(0);
		it->second->Play(0, 0, times - 1);
	}
}

void Sound::Stop(const std::string& name)
{
	if (name.empty() == true)
	{
		for (std::map<std::string, IDirectSoundBuffer8*>::iterator it = m_soundBufferMap.begin(); it != m_soundBufferMap.
		     end(); ++it)
		{
			it->second->Stop();
			it->second->SetCurrentPosition(0);
		}
	}
	else
	{
		std::map<std::string, IDirectSoundBuffer8*>::iterator it = m_soundBufferMap.find(name);
		if (it == m_soundBufferMap.end())
			return;
		it->second->Stop();
	}
}

bool Sound::IsPlaying(const std::string & name)
{
	std::map<std::string, IDirectSoundBuffer8*>::iterator it;

	it = m_soundBufferMap.find(name);
	if (it == m_soundBufferMap.end())
		return false;

	DWORD result;
	it->second->GetStatus(&result);
	if (result == DSBSTATUS_PLAYING)
		return true;

	return false;
}

void Sound::SetVolume(float percentage, const std::string& name)
{
	m_volume = percentage;
	if (name.empty() == true)
	{
		long volume = (percentage) / 100 * (- DSBVOLUME_MIN) + DSBVOLUME_MIN;
		for (std::map<std::string, IDirectSoundBuffer8*>::iterator it = m_soundBufferMap.begin(); it != m_soundBufferMap.end(); ++it)
		{
			it->second->SetVolume(volume);
		}
	}
	else
	{
		std::map<std::string, IDirectSoundBuffer8*>::iterator it = m_soundBufferMap.find(name);
		if (it == m_soundBufferMap.end())
			return;
		long volume = (percentage) / 100 * (- DSBVOLUME_MIN) + DSBVOLUME_MIN;
		it->second->SetVolume(volume);
	}
}

void Sound::Mute()
{
	m_isMute = true;
	GetInstance()->Stop();
}

void Sound::UnMute()
{
	m_isMute = false;
}

void Sound::CleanUp() const
{
	delete this;
}
