#ifndef BREAK_OUT_BRICK
#define BREAK_OUT_BRICK

#include "cocos2d.h"
#include "PhysicsSprite.h"
#include "PhysicsProtocol.h"

USING_NS_CC;


class GameBrick :public PhysicsSprite,public PhysicsProtocol
{
public:
	GameBrick();
	~GameBrick();

private:
	//type 1 = long ,0 = short
	CC_SYNTHESIZE(bool, is_longBrick, IsLong);
	CC_SYNTHESIZE(int, lifePoint, LifePoint);
};



#endif