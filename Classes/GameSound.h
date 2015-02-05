#ifndef BREAK_OUT_SOUND
#define BREAK_OUT_SOUND

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "SoundDelegate.h"
#include "GameData.h"

USING_NS_CC;
USING_NS_CCD;

class GameSound :public SoundDelegate
{
public:
	static GameSound* getInstance();

	GameSound();

	~GameSound();

	void preLoad();

	void unLoad(std::string file);

public:

	CC_SYNTHESIZE(bool, music_on, MusicOn);

	CC_SYNTHESIZE(bool, effect_on, EffectOn);

	virtual bool isMusicOn() override;

	virtual bool isEffectOn() override;

	virtual void musicOn() override;

	virtual void musicOff() override;

	virtual void effectOn() override;

	virtual void effectOff() override;

	virtual void playBackgroundMusic() override;

	virtual void playClickEffect() override;

	virtual void playSwitchEffect() override;

private:
	static GameSound*  _gameSound;

	SimpleAudioEngine* _audioEngine;
};








#endif