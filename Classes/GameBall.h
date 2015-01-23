#ifndef BREAK_OUT_BALL
#define BREAK_OUT_BALL

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GameData.h"

USING_NS_CC;

class GameBall :public Sprite
{
public:
	CREATE_FUNC(GameBall);

	virtual bool init() override;

private:
	std::string selectRandomColor();

	void initSelf();

	void initPhysicsAttributes();

};










#endif