#include "Explosion.h"


Explosion::Explosion()
{
	m_RayFixture = nullptr;
}

Explosion::~Explosion()
{

}
float32 Explosion::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction)
{
	m_RayFixture = fixture;
	m_RayPoint = point;
	m_RayNormal = normal;
	m_RayFraction = fraction;
//	GameBrick* brick = (GameBrick*)fixture->GetBody()->GetUserData();
	CCLOG("%f,brick~~~~~~~~~~~~~~", m_RayFraction);
	return fraction;
}
