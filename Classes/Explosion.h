#ifndef BREAK_OUT_EXPLOSION
#define BREAK_OUT_EXPLOSION

#include "GameBrick.h"

class Explosion:public b2RayCastCallback
{
public:
	virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction) override;
	Explosion();
	~Explosion();
private:
	b2Fixture  *m_RayFixture;
	b2Vec2      m_RayPoint;
	b2Vec2      m_RayNormal;
	float32     m_RayFraction;
private:
	
	
};


#endif