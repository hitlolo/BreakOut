#pragma once

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

	virtual void playClickEffect() = 0;

	virtual void playSwitchEffect() = 0;
};