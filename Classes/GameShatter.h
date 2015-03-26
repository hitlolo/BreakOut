#ifndef BREAK_OUT_SHATTER
#define BREAK_OUT_SHATTER


#include "cocos2d.h"
#include "GameBrick.h"
#include "Explosion.h"
#include "math\CCMath.h"
USING_NS_CC;

class GameBrick;
class GameShatter :public Node, public PhysicsProtocol, public b2RayCastCallback
{

public:
	static GameShatter* create(GameBrick* target, b2Vec2 point);
	virtual bool init() override;
	
	GameShatter(GameBrick* target, b2Vec2 point);
	~GameShatter();
private:
	b2Vec2 resetOffset(b2Vec2 point);
private:
	int         m_cut;
	b2Vec2      m_collidePoint; //int world
	GameBrick  *m_target;
	b2Body     *m_targetBody;
	b2World    *m_world;
	DrawNode   *m_draw;


public:
	virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;
private:
	b2Fixture  *m_RayFixture;
	b2Vec2      m_RayPoint;
	b2Vec2      m_RayNormal;
	float32     m_RayFraction;

private:
	std::vector<b2Body*> targetBody_vector;
	void bomb();

	float getRandomAngle();
};

#endif