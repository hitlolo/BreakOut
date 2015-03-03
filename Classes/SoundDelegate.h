#pragma once

typedef enum class melody
{
	DO = 0,
	RE,
	MI,
	FA,
	SO,
	LA,
	XI
}MELODY;

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

	virtual void playMelody(MELODY melody) = 0;

	virtual void end() = 0;
};