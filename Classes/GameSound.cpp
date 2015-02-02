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
	SimpleAudioEngine::getInstance()->preloadEffect("click1.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("click2.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("rollover1.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("rollover2.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("rollover2.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("switch2.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("switch3.ogg");
	
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

void GameSound::musicOn()
{
	setMusicOn(true);
}


void GameSound::musicOff()
{
	setMusicOn(false);
}

void GameSound::effectOn()
{
	setEffectOn(true);
}

void GameSound::effectOff()
{
	setEffectOn(false);
}

void GameSound::playBackgroundMusic()
{
	if (!music_on)
		return;

}

void GameSound::playClickEffect()
{
	if (!effect_on)
		return;
	SimpleAudioEngine::getInstance()->playEffect("click1.ogg");
}
void GameSound::playSwitchEffect()
{
	if (!effect_on)
		return;
	SimpleAudioEngine::getInstance()->playEffect("switch2.ogg");
}