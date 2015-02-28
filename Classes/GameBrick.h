#ifndef BREAK_OUT_BRICK
#define BREAK_OUT_BRICK

#include "cocos2d.h"
#include "PhysicsSprite.h"
#include "PhysicsProtocol.h"
#include "GB2ShapeCache-x.h"

USING_NS_CC;


class GameBrick :public PhysicsSprite,public PhysicsProtocol
{
public:
	static GameBrick* create(b2World*,Value&);
	bool init(b2World*,Value&);
	GameBrick();
	~GameBrick();

private:
	void initBrick(b2World*, Value&);
	void initImage(Value&);
	void initLife(Value&);
	void initType(Value&);
	void initPhysics(b2World*, Value&);

	std::string getBrickColor(Value &def);
	std::string getLongBrickColor(Value &def);
	std::string getShortBrickColor(Value &def);
	std::string getShapeName();
	//type 1 = long ,0 = short
	CC_SYNTHESIZE(bool, is_longBrick, IsLong);
	CC_SYNTHESIZE(int, lifePoint, LifePoint);
};



#endif