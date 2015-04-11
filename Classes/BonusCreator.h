#ifndef BREAK_OUT_BONUS_CREATOR
#define BREAK_OUT_BONUS_CREATOR

#include "cocos2d.h"
#include "LotteryData.h"
#include "BonusStrategy.h"

USING_NS_CC;

class BonusCreator
{
private:
	static BonusCreator*  _bonusCreator;

public:
	static BonusCreator* getInstance();
	BonusCreator();
	~BonusCreator();
	PhysicsSprite* createBonus(Lottery  type, b2World* world, Point position);

};
#endif