#ifndef BREAK_OUT_AABB
#define BREAK_OUT_AABB

#include "cocos2d.h"
#include "ContactData.h"
#include "Box2D\Box2D.h"
USING_NS_CC;

class AABBQuery : public b2QueryCallback
{
public:
	AABBQuery();
	~AABBQuery();
	bool ReportFixture(b2Fixture* fixture);
	std::vector<b2Body*> getInScreenBodies();
private:
	std::vector<b2Body*> inScreenBodies;
};

#endif