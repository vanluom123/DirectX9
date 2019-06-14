#include "Sound.h"
#include "GameGlobal.h"

Sound* Sound::_instance = NULL;

Sound* Sound::getInstance()
{
	if (_instance == NULL)
		_instance = new Sound(GameGlobal::getWnd());
	return _instance;
}

Sound::Sound(HWND hWnd) : _volume(75.0f), _isMute(false)
{
	_primaryBuffer = NULL;

	DSBUFFERDESC bufferDesc; //describe the buffer

	HRESULT result = DirectSoundCreate8(NULL, &_pDevice, NULL);
	if (result != S_OK)
		return;

	result = _pDevice->SetCooperativeLevel(hWnd, DSSCL_PRIORITY); // set the cooperative level.
	if (result != S_OK)
		return;

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	result = _pDevice->CreateSoundBuffer(&bufferDesc, &_primaryBuffer, NULL);
	if (result != S_OK)
		return;
	

	// -----------LOAD SOUND-----------

	// Blast hornet sound
	loadSound("Resources/Sound/Blast Hornet.wav", "BlastHornet");

	// RockMan sound
	loadSound("Resources/Sound/Shooting bullet.wav", "ShootingBullet");
	loadSound("Resources/Sound/Absorb energy.wav", "AbsorbShortEnergy");
	loadSound("Resources/Sound/Absorb long energy.wav", "AbsorbLongEnergy");
	loadSound("Resources/Sound/Give up short energy.wav", "GiveUpShortEnergy");
	loadSound("Resources/Sound/Give up long energy.wav", "GiveUpLongEnergy");
	loadSound("Resources/Sound/Fall down ground.wav", "FallDownGround");
	loadSound("Resources/Sound/Die.wav", "RockmanDie");
	loadSound("Resources/Sound/jump.wav", "JumpUp");//Use to jump and to cling
	loadSound("Resources/Sound/dash.wav", "dash");

	// Enemies explosion
	loadSound("Resources/Sound/explosions.wav", "explosions");
}

Sound::~Sound()
{
	for (std::map<std::string, IDirectSoundBuffer8*>::iterator it = _soundBufferMap.begin(); it != _soundBufferMap.end(); ++it)
	{
		if (it->second)
		{
			it->second->Release();
			it->second = NULL;
		}
	}
	if (_primaryBuffer)
		_primaryBuffer->Release();
	if (_pDevice)
		_pDevice->Release();
	_pDevice = NULL;

	_primaryBuffer = NULL;
}

void Sound::create(HWND hWnd)
{
	if (_instance == NULL)
		_instance = new Sound(hWnd);
}

float Sound::getVolume() const
{
	return _volume;
}

void Sound::loadSound(char* fileName, const std::string& name)
{
	if (_soundBufferMap.find(name) != _soundBufferMap.end())
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
	//fread(&waveFileHeader, sizeof(waveFileHeader), 1, filePtr);

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
	//IDirectSoundBuffer8

	//long result = pDevice->CreateSoundBuffer(&bufferDesc, &secondaryBuffer, NULL);

	_pDevice->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);

	long result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, reinterpret_cast<void**>(&(*pSecondaryBuffer)));

	tempBuffer->Release();
	tempBuffer = NULL;

	if (FAILED(result))
		return;

	//fseek(filePtr, sizeof(WaveHeaderStruct), SEEK_SET); // move the filePointer cursor to data section

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

	long tempVolume = (_volume) / 100 * (- DSBVOLUME_MIN) + DSBVOLUME_MIN;
	(*pSecondaryBuffer)->SetVolume(tempVolume);

	_soundBufferMap[name] = secondaryBuffer;
}

void Sound::play(const std::string& name, bool infiniteLoop, int times)
{
	if (_isMute == true || isPlaying(name) == true)
		return;

	std::map<std::string, IDirectSoundBuffer8*>::iterator it;
	it = _soundBufferMap.find(name);
	if (it == _soundBufferMap.end())
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

void Sound::stop(const std::string& name)
{
	if (name.empty() == true)
	{
		for (std::map<std::string, IDirectSoundBuffer8*>::iterator it = _soundBufferMap.begin(); it != _soundBufferMap.
		     end(); ++it)
		{
			it->second->Stop();
			it->second->SetCurrentPosition(0);
		}
	}
	else
	{
		std::map<std::string, IDirectSoundBuffer8*>::iterator it = _soundBufferMap.find(name);
		if (it == _soundBufferMap.end())
			return;
		it->second->Stop();
	}
}

bool Sound::isPlaying(const std::string & name)
{
	std::map<std::string, IDirectSoundBuffer8*>::iterator it;

	it = _soundBufferMap.find(name);
	if (it == _soundBufferMap.end())
		return false;

	DWORD result;
	it->second->GetStatus(&result);
	if (result == DSBSTATUS_PLAYING)
		return true;

	return false;
}

void Sound::setVolume(float percentage, const std::string& name)
{
	_volume = percentage;
	if (name.empty() == true)
	{
		long volume = (percentage) / 100 * (- DSBVOLUME_MIN) + DSBVOLUME_MIN;
		for (std::map<std::string, IDirectSoundBuffer8*>::iterator it = _soundBufferMap.begin(); it != _soundBufferMap.end(); ++it)
		{
			it->second->SetVolume(volume);
		}
	}
	else
	{
		std::map<std::string, IDirectSoundBuffer8*>::iterator it = _soundBufferMap.find(name);
		if (it == _soundBufferMap.end())
			return;
		long volume = (percentage) / 100 * (- DSBVOLUME_MIN) + DSBVOLUME_MIN;
		it->second->SetVolume(volume);
	}
}

void Sound::mute()
{
	_isMute = true;
	getInstance()->stop();
}

void Sound::unMute()
{
	_isMute = false;
}

void Sound::cleanUp() const
{
	delete this;
}
