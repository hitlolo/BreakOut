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
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("rockyou.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("click1.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("click2.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("rollover1.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("rollover2.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("rollover2.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("switch2.ogg");
	SimpleAudioEngine::getInstance()->preloadEffect("switch3.ogg");

	//MELODY
	SimpleAudioEngine::getInstance()->preloadEffect("do.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("re.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("mi.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("fa.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("so.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("la.wav");
	
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
	bool isPlaying = SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
	if (!isPlaying)
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("rockyou.mp3", true);
	}
}


void GameSound::musicOff()
{
	setMusicOn(false);
	bool isPlaying = SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
	if (isPlaying)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
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

	SimpleAudioEngine::getInstance()->playBackgroundMusic("rockyou.mp3", true);
}

void GameSound::stopBackgroundMusic()
{
	if (!music_on)
		return;
	bool isPlaying = SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
	if (isPlaying)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}
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

void GameSound::playMelody(MELODY melody)
{
	if (!effect_on)
		return;
	switch (melody)
	{
	case MELODY::DO:
		SimpleAudioEngine::getInstance()->playEffect("do.wav");
		break;
	case MELODY::RE:
		SimpleAudioEngine::getInstance()->playEffect("re.wav");
		break;
	case MELODY::MI:
		SimpleAudioEngine::getInstance()->playEffect("mi.wav");
		break;
	case MELODY::FA:
		SimpleAudioEngine::getInstance()->playEffect("fa.wav");
		break;
	case MELODY::SO:
		SimpleAudioEngine::getInstance()->playEffect("so.wav");
		break;
	case MELODY::LA:
		SimpleAudioEngine::getInstance()->playEffect("la.ogg");
		break;
	case MELODY::XI:
		break;

	}
}


void GameSound::end()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
	bool isPlaying = SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
	if (isPlaying)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}

	SimpleAudioEngine::getInstance()->end();
}