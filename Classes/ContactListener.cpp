#include "ContactListener.h"


CustomContact::CustomContact(b2Contact* contact)
{
	m_fixtureA = contact->GetFixtureA();
	m_fixtureB = contact->GetFixtureB();
}

CustomContact::~CustomContact()
{
	m_fixtureA = nullptr;
	m_fixtureB = nullptr;
}

b2Fixture* CustomContact::getBrickFixture()
{
	b2Filter filterA = m_fixtureA->GetFilterData();
	b2Filter filterB = m_fixtureB->GetFilterData();
	if (filterA.categoryBits == (uint16)collide_bit::BRICK)
	{
		return m_fixtureA;
	}
	else
	{
		return m_fixtureB;
	}

}

bool CustomContact::isBallAndBrick()
{
	b2Filter filterA = m_fixtureA->GetFilterData();
	b2Filter filterB = m_fixtureB->GetFilterData();
	if (filterA.categoryBits == (uint16)collide_bit::BALL
		&&filterB.categoryBits == (uint16)collide_bit::BRICK)
	{
		return true;
	}
	else if
		(filterB.categoryBits == (uint16)collide_bit::BALL
		&&filterA.categoryBits == (uint16)collide_bit::BRICK)
	{
		return true;
	}
	else
		return false;
}
bool CustomContact::isBallAndPaddle()
{
	b2Filter filterA = m_fixtureA->GetFilterData();
	b2Filter filterB = m_fixtureB->GetFilterData();
	if (filterA.categoryBits == (uint16)collide_bit::BALL
		&&filterB.categoryBits == (uint16)collide_bit::PADDLE)
	{
		return true;
	}
	else if
		(filterB.categoryBits == (uint16)collide_bit::BALL
		&&filterA.categoryBits == (uint16)collide_bit::PADDLE)
	{
		return true;
	}
	else
		return false;
}
bool CustomContact::isBallAndWall()
{
	b2Filter filterA = m_fixtureA->GetFilterData();
	b2Filter filterB = m_fixtureB->GetFilterData();
	if (filterA.categoryBits == (uint16)collide_bit::BALL
		&&filterB.categoryBits == (uint16)collide_bit::WALL)
	{
		return true;
	}
	else if
		(filterB.categoryBits == (uint16)collide_bit::BALL
		&&filterA.categoryBits == (uint16)collide_bit::WALL)
	{
		return true;
	}
	else
		return false;
}
bool CustomContact::isBallAndBottom()
{
	b2Filter filterA = m_fixtureA->GetFilterData();
	b2Filter filterB = m_fixtureB->GetFilterData();
	if (filterA.categoryBits == (uint16)collide_bit::BALL
		&&filterB.categoryBits == (uint16)collide_bit::BOTTOM)
	{
		return true;
	}
	else if
		(filterB.categoryBits == (uint16)collide_bit::BALL
		&&filterA.categoryBits == (uint16)collide_bit::BOTTOM)
	{
		return true;
	}
	else
		return false;
}
collide_type CustomContact::getCollideType()
{
	if (isBallAndWall())
	{
		return  collide_type::BALL_WALL;
	}
	else if (isBallAndBrick())
	{
		return collide_type::BALL_BRICK;
	}
	else if (isBallAndBottom())
	{
		return collide_type::BALL_BOTTOM;
	}
	else if (isBallAndPaddle())
	{
		return collide_type::BALL_PADDLE; 
	}
	else return collide_type::UNKNOWN;
}

//----------------------------------------------------------
//----------------------------------------------------------

void ContactListener::BeginContact(b2Contact* contact)  // Called when two fixtures begin to touch.
{
	if (contact)
	{
		CustomContact myContact(contact);
		contactVector.push_back(myContact);
		
	}
}
void ContactListener::EndContact(b2Contact* contact)   // Called when two fixtures cease to touch.
{
	CustomContact myContact(contact);
	std::vector<CustomContact>::iterator pos;
	pos = std::find(contactVector.begin(), contactVector.end(), myContact);
	if (pos != contactVector.end()) 
	{
		contactVector.erase(pos);
	}
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	B2_NOT_USED(contact);
	B2_NOT_USED(oldManifold);
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	B2_NOT_USED(contact);
	B2_NOT_USED(impulse);
}


std::vector<CustomContact>& ContactListener::getContactVector()
{
	return contactVector;
}
