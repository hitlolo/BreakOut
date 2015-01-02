#include "GameSound.h"

GameSound* GameSound::_gameSound = nullptr;

GameSound* GameSound::getInstance()
{
	if (_gameSound == nullptr)
	{
		_gameSound = new GameSound();
		return _gameSound;
	}
	return
		_gameSound;
}

GameSound::GameSound() :music_on(true), effect_on(true)
{
	_audioEngine = SimpleAudioEngine::getInstance();
}

GameSound::~GameSound()
{
	CC_SAFE_DELETE(_gameSound);
}

void GameSound::preLoad()
{
	//load music and effects...
}

void  GameSound::unLoad(std::string file)
{
	_audioEngine->unloadEffect(file.c_str());
}

bool GameSound::isMusicOn()
{
	return getMusicOn();
}

bool GameSound::isEffectOn()
{
	return getEffectOn();
}

void GameSound::playBackgroundMusic()
{
	if (!music_on)
		return;

}