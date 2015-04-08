#pragma once

#include  "SoundData.h"

class SoundDelegate
{
public:

	virtual bool isMusicOn() = 0;
	virtual bool isEffectOn() = 0;

	virtual void musicOn() = 0;
	virtual void musicOff() = 0;

	virtual void effectOn() = 0;
	virtual void effectOff() = 0;

	virtual void playBackgroundMusic() = 0;
	virtual void stopBackgroundMusic() = 0;
	virtual void playClickEffect() = 0;
	virtual void playSwitchEffect() = 0;
	virtual void playSwingEffect() = 0;

	virtual void playMelody(MELODY melody) = 0;

	virtual void end() = 0;
	virtual void pause() = 0;
	virtual void resume() = 0;
};