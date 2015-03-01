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
	static GameBall* create(b2World*,b2Body*);
	virtual bool init() override;
	GameBall(b2World*, b2Body*);
	~GameBall();
	void startGame();
	void update(float time) override;
public:
	void onBeginMove(const b2Vec2 position);
	void onMove(const std::vector<Touch*>& touches);
	void onMoveEnd();
	void onMoveCancel();
private:
	std::string selectRandomColor();
	void initSelfImage();
	void initPhysicsAttributes();	
	void beReady();

private:
	b2World          *m_world;
	b2Body           *m_groundBody;
	b2MouseJoint     *m_mouseJoint;
	b2PrismaticJoint *m_joint_x;
	int               m_maxSpeed;
	CC_SYNTHESIZE(bool, isStarted, Started);
	
};










#endif