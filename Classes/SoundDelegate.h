#pragma once

class SoundDelegate
{
public:

	virtual bool isMusicOn() = 0;

	virtual bool isEffectOn() = 0;

	virtual void playBackgroundMusic() = 0;

};