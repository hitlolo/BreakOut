#ifndef BREAK_OUT_SOUND
#define BREAK_OUT_SOUND

#include "cocos2d.h"
#include "audio/include/AudioEngine.h"
#include "SimpleAudioEngine.h"
#include "SoundDelegate.h"
#include "GameData.h"

USING_NS_CC;
USING_NS_CCD;
//using namespace experimental;
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
	virtual void stopBackgroundMusic() override;
	virtual void playClickEffect() override;
	virtual void playSwitchEffect() override;
	virtual void playSwingEffect() override;

	virtual void playMelody(MELODY melody) override;

	virtual void end() override;
	virtual void pause() override;
	virtual void resume() override;

private:
	static GameSound*  _gameSound;
//	SimpleAudioEngine* _audioEngine;

private:
	int background_id;
};








#endif