#ifndef BREAK_OUT_CONTACT
#define BREAK_OUT_CONTACT

#include "cocos2d.h"
#include "Box2D\Box2D.h"
USING_NS_CC;

typedef enum class collide_bit
{
	BOTTOM = 8,
	BALL = 1,
	PADDLE = 2,
	BRICK = 4,
	WALL = 16,

}COLLIDE_BIT;

typedef enum class collide_type
{
	BALL_WALL = 0,
	BALL_BOTTOM,
	BALL_BRICK,
	BALL_PADDLE,
	UNKNOWN

}COLLIDE_TYPE;

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
	collide_type getCollideType();
	b2Fixture* getBrickFixture();

};

class ContactListener :public b2ContactListener
{
public:

	virtual void BeginContact(b2Contact* contact);  // Called when two fixtures begin to touch.
	virtual void EndContact(b2Contact* contact);    // Called when two fixtures cease to touch.
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);

public:
	std::vector<CustomContact>& getContactVector();

private:
	std::vector<CustomContact> contactVector;
};



#endif