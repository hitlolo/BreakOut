#ifndef BREAK_OUT_SHATTER
#define BREAK_OUT_SHATTER


#include "cocos2d.h"
#include "GameBrick.h"
#include "math\CCMath.h"
#include "ShatterSprite.h"
#include "ContactData.h"
#include <map> 
USING_NS_CC;

class GameBrick;
class GameShatter :public Node, public PhysicsProtocol, public b2RayCastCallback
{

public:
	static GameShatter* create(GameBrick* target, b2Vec2 point);
	virtual bool init() override;
	
	GameShatter(GameBrick* target, b2Vec2 point);
	~GameShatter();

	void bomb();
private:
	void resetOffsetX(b2Vec2& point);
	void resetOffsetY(b2Vec2& point);
	void resetOffset(b2Vec2& point);
	bool checkSliceAngle(float angle);
private:
	float       m_left;
	float       m_right;
	float       m_up;
	float       m_bottom;
	int         m_cut;
	b2Vec2      m_collidePoint; //int world
	b2Vec2      m_exploPoint;
	float       m_explosionRadius;
	GameBrick  *m_target;
	b2Vec2      m_targetLocation;
	Texture2D  *m_originTexture;
	b2Body     *m_targetBody;
//	b2PolygonShape *m_targetShape;
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
	std::vector<float>          sliceAngle_vector;
	std::vector<b2Body*>        targetBody_vector;
	std::vector<b2Body*>        slicedBody_vector;
	std::vector<b2Body*>        newBody_vector;
	std::map<b2Body*, b2Vec2>   targetBody_map;
	std::vector<ShatterSprite*> shatter_vector;

//	std::vector<PhysicsSprite*> slicedSprite_vector;
	
	void   initBoundary();
	b2Vec2 getExploPoint();
	float getRandomAngle();
	void  splitBrick(b2Body* body, b2Vec2& start, b2Vec2& end);
	bool  createShatter(b2Body*, std::vector<b2Vec2>);
	float det(float x1, float y1, float x2, float y2, float x3, float y3);
	void  arrangeClockwise(std::vector<b2Vec2>);
	bool  compare(b2Vec2 a,b2Vec2 b);
	float getArea(std::vector<b2Vec2> vector);
	void  removeTargetBodyAndPoint(b2Body* body);
	float32 sb2Cross(const b2Vec2& a, const b2Vec2& b);
	bool CheckSegmentLength(std::vector<b2Vec2>);
	bool pointInBody(const b2Vec2& point);

	bool PointCompare(const b2Vec2 &a, const b2Vec2 &b, const b2Vec2 &center);
	void ClockwiseSortPoints(std::vector<b2Vec2> &vector);
	b2Vec2 setExplosionVelocity(b2Body* body);
	void  createNewBodyAndNewSprite();
	void  cleanOldBodyAndSprite();
};

#endif