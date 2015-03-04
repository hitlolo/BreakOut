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

GameSound::GameSound() :music_on(true), effect_on(true), background_id(-1)
{
	_audioEngine = SimpleAudioEngine::getInstance();

}

GameSound::~GameSound()
{
	_audioEngine = nullptr;
	CC_SAFE_DELETE(_gameSound);
	_gameSound = nullptr;
	
}

void GameSound::end()
{
	//SimpleAudioEngine::getInstance()->stopAllEffects();
	//bool isPlaying = SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
	//if (isPlaying)
	//{
	//	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	//}


	//_audioEngine->getInstance()->end();
	
	//_audioEngine = nullptr;
	experimental::AudioEngine::stopAll();
	//experimental::AudioEngine::uncacheAll();
	experimental::AudioEngine::end();
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
	this->playBackgroundMusic();
}


void GameSound::musicOff()
{
	setMusicOn(false);
	this->stopBackgroundMusic();
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

//	bool isPlaying = SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
	if (background_id == experimental::AudioEngine::INVALID_AUDIO_ID)
	{
		background_id = experimental::AudioEngine::play2d("rockyou.mp3", true);
	}
	else
	{
		auto isPlaying = experimental::AudioEngine::getState(background_id);
		if (isPlaying == experimental::AudioEngine::AudioState::PLAYING)
		{
			return;
		}
		else
		{
			//SimpleAudioEngine::getInstance()->playBackgroundMusic("rockyou.mp3", true);
			background_id = experimental::AudioEngine::play2d("rockyou.mp3", true);
		}
	}
	
}

void GameSound::stopBackgroundMusic()
{

	//bool isPlaying = SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying();
	//if (isPlaying)
	//{
	//	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	//}

	auto isPlaying = experimental::AudioEngine::getState(background_id);
	if (isPlaying == experimental::AudioEngine::AudioState::PLAYING)
	{
		experimental::AudioEngine::stop(background_id);
	}
	
}

void GameSound::playClickEffect()
{
	if (!effect_on)
		return;
	//SimpleAudioEngine::getInstance()->playEffect("click1.ogg");
	experimental::AudioEngine::play2d("click1.ogg", false);
}

void GameSound::playSwitchEffect()
{
	if (!effect_on)
		return;
	//SimpleAudioEngine::getInstance()->playEffect("switch2.ogg");
	experimental::AudioEngine::play2d("switch2.ogg", false);
}

void GameSound::playMelody(MELODY melody)
{
	if (!effect_on)
		return;
	switch (melody)
	{
	case MELODY::DO:
		//SimpleAudioEngine::getInstance()->playEffect("melody/do.wav");
		experimental::AudioEngine::play2d("melody/do.wav", false);
		break;
	case MELODY::RE:
		//SimpleAudioEngine::getInstance()->playEffect("melody/re.wav");
		experimental::AudioEngine::play2d("melody/re.wav", false);
		break;
	case MELODY::MI:
		//SimpleAudioEngine::getInstance()->playEffect("melody/mi.wav");
		experimental::AudioEngine::play2d("melody/mi.wav", false);
		break;
	case MELODY::FA:
		//SimpleAudioEngine::getInstance()->playEffect("melody/fa.wav");
		experimental::AudioEngine::play2d("melody/fa.wav", false);
		break;
	case MELODY::SO:
		//SimpleAudioEngine::getInstance()->playEffect("melody/so.wav");
		experimental::AudioEngine::play2d("melody/so.wav", false);
		break;
	case MELODY::LA:
		//SimpleAudioEngine::getInstance()->playEffect("melody/la.ogg");
		experimental::AudioEngine::play2d("melody/la.wav", false);
		break;
	case MELODY::XI:
		break;

	}
}


