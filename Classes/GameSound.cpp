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
	SimpleAudioEngine::getInstance()->preloadEffect("melody/do.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("melody/re.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("melody/mi.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("melody/fa.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("melody/so.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("melody/la.wav");
	
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

	bool isPlaying = SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
	if (isPlaying)
	{
		return;
	}
	else
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("rockyou.mp3", true);
	}
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
		SimpleAudioEngine::getInstance()->playEffect("melody/do.wav");
		break;
	case MELODY::RE:
		SimpleAudioEngine::getInstance()->playEffect("melody/re.wav");
		break;
	case MELODY::MI:
		SimpleAudioEngine::getInstance()->playEffect("melody/mi.wav");
		break;
	case MELODY::FA:
		SimpleAudioEngine::getInstance()->playEffect("melody/fa.wav");
		break;
	case MELODY::SO:
		SimpleAudioEngine::getInstance()->playEffect("melody/so.wav");
		break;
	case MELODY::LA:
		SimpleAudioEngine::getInstance()->playEffect("melody/la.ogg");
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