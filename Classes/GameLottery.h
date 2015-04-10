#ifndef BREAK_OUT_LOTTERY
#define BREAK_OUT_LOTTERY


#include "cocos2d.h"
#include "LotteryData.h"


USING_NS_CC;

class  GameLottery
{
public:
	
	static  GameLottery*  getInstance();
	GameLottery();
	~GameLottery();

public:
	LOTTERY lottery();
	//PhysicsSprite* bonus(LOTTERY type, Point position);
private:
	static GameLottery*   _gameLottery;
	std::random_device randomDevice;
	std::mt19937*      _mt;

	int getRandomByRange(int from, int to);
	float getRandomByRange(float from, float to);
	bool isBonus();
	int buffOrDebuffOrRandom();
	LOTTERY getBuff(); 
	LOTTERY getDeBuff();
	LOTTERY getRandom(); 
};


#endif