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
	static GameBall* create(b2World*, b2Body*, b2Vec2 = b2Vec2(9, 3), ball_state = ball_state::TO_BE_START,b2Vec2 = b2Vec2(0,0));
	bool init(b2Vec2, ball_state, b2Vec2);
	GameBall(b2World*, b2Body*);
	virtual ~GameBall();
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


	void initByStateAndPositionAndVelocity(ball_state,b2Vec2,b2Vec2);
	void initStartPhysicsAttributes(b2Vec2 position);
	void initBonusPhysicsAttributes(b2Vec2 position, b2Vec2 velocity);
	void initReStartPhysicsAttributes(b2Vec2 position);

private:
	b2World          *m_world;
	b2Body           *m_groundBody;
	b2MouseJoint     *m_mouseJoint;
	b2PrismaticJoint *m_joint_x;
	int               m_currentSpeed;
	int               m_minSpeed;
	int               m_maxSpeed;
	int               m_normalSpeed;
	CC_SYNTHESIZE(bool, isStarted, Started);
	
	
	CC_SYNTHESIZE(bool, is_SpeedUp, SpeedUpEd);
	CC_SYNTHESIZE(bool, is_SpeedDown, SpeedDownEd);
	CC_SYNTHESIZE(unsigned, bonusTime, BonusTime);
	void bonusTimeCountingDown(float delta);
public:
	int speedUp(unsigned time);
	int speedDown(unsigned time);
};










#endif