#ifndef BREAK_OUT_CONTACT
#define BREAK_OUT_CONTACT

#include "cocos2d.h"
#include "ContactData.h"
#include "Box2D\Box2D.h"
USING_NS_CC;



class CustomContact
{
public:
	CustomContact(b2Contact* contact);
	~CustomContact();
	b2Fixture  *m_fixtureA;
	b2Fixture  *m_fixtureB;
	bool operator==(const CustomContact& other) const
	{
		return (m_fixtureA == other.m_fixtureA) && (m_fixtureB == other.m_fixtureB);
	}
public:
	bool isBallAndBrick();
	bool isBallAndPaddle();
	bool isBallAndWall();
	bool isBallAndBottom();

	bool isBonusAndBottom();
	bool isPaddleAndBonus();

	bool isPaddleAndFruit();
	bool isPaddleAndBallBonus();
	bool isPaddleAndUp();
	bool isPaddleAndDown();
	bool isPaddleAndSpeedUp();
	bool isPaddleAndSpeedDown();
	bool isPaddleAndQuestion();
	bool isPaddleAndExcalmation();
	bool isPaddleAndBad();

	

	b2Vec2 getContactPoint();
	collide_type getCollideType();
	collide_type getBonusType();
	b2Fixture* getBrickFixture();
	b2Fixture* getBonusFixture();
private:
	b2WorldManifold m_manifold;
};

class ContactListener :public b2ContactListener
{
public:

	virtual void BeginContact(b2Contact* contact);  // Called when two fixtures begin to touch.
	virtual void EndContact(b2Contact* contact);    // Called when two fixtures cease to touch.
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

public:
	std::vector<CustomContact> getContactVector();

private:
	std::vector<CustomContact> contactVector;
};



#endif