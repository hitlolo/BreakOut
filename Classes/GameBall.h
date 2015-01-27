#ifndef BREAK_OUT_BALL
#define BREAK_OUT_BALL

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "PhysicsSprite.h"
#include "GameData.h"
#include "PhysicsProtocol.h"
#include "GB2ShapeCache-x.h"


USING_NS_CC;

class GameBall :public PhysicsSprite, public PhysicsProtocol
{
public:
	static GameBall* create(b2World*);

	virtual bool init() override;

	GameBall(b2World*);
	
	~GameBall();
private:
	std::string selectRandomColor();

	void initSelfImage();

	void initPhysicsAttributes();

	void beReady();

	void startGame();

private:
	b2World* m_world;
};










#endif