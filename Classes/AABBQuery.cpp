#include "AABBQuery.h"

AABBQuery::AABBQuery()
{

}

AABBQuery::~AABBQuery()
{
	inScreenBodies.clear();
}

bool AABBQuery::ReportFixture(b2Fixture* fixture)
{
	b2Body* body = fixture->GetBody();
	this->inScreenBodies.push_back(body);
	return true;
}

std::vector<b2Body*> AABBQuery::getInScreenBodies()
{
	return inScreenBodies;
}