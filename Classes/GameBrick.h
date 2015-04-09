#ifndef BREAK_OUT_BRICK
#define BREAK_OUT_BRICK

#include "cocos2d.h"
#include "PhysicsSprite.h"
#include "PhysicsProtocol.h"
#include "GB2ShapeCache-x.h"
#include "GameSound.h"
#include "GameShatter.h"

USING_NS_CC;

class GameShatter;
class GameBrick :public PhysicsSprite,public PhysicsProtocol
{
public:
	static GameBrick* create(b2World*,Value&);
	bool init(b2World*,Value&);
	GameBrick();
	~GameBrick();
	b2Vec2 getOriginLocation();
	CC_SYNTHESIZE(int, coinPoint, CoinPoint);
//	virtual void update(float time) override;

private:
	void initBrick(b2World*, Value&);
	void initImage(Value&);
	void initHP(Value&);
	void initCoinPoint();
	void initCoinLabel();
	void initType(Value&);
	void initPhysics(b2World*, Value&);
	void initMelodyType(Value&);
	void setOriginLocation();
	melody& getMelodyType();

	std::string getBrickColor(Value &def);
	std::string getLongBrickColor(Value &def);
	std::string getShortBrickColor(Value &def);
	std::string getShapeName();

	melody melodyType;
	//type 1 = long ,0 = short
	CC_SYNTHESIZE(bool, is_longBrick, IsLong);
	CC_SYNTHESIZE(int, hpPoint, HpPoint);
	

public:
	//return hp
	int collision(b2Vec2 point);

private:
	void shake();
	void PlayMelody();
	void hpDown();
	void coinLabelJump();
	void collapse(Point point);
	void explosion();

private:
	b2Vec2 originLocation;
	Label  *m_label;
};



#endif