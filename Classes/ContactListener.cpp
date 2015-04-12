#include "ContactListener.h"


CustomContact::CustomContact(b2Contact* contact)
{
	m_fixtureA = contact->GetFixtureA();
	m_fixtureB = contact->GetFixtureB();

	//b2Filter filterA = m_fixtureA->GetFilterData();
	//b2Filter filterB = m_fixtureB->GetFilterData();
	//CCLOG("%d,%d", filterA.categoryBits, filterB.categoryBits);
	//m_manifold = new b2WorldManifold();
	contact->GetWorldManifold(&m_manifold);
}

CustomContact::~CustomContact()
{
	m_fixtureA = nullptr;
	m_fixtureB = nullptr;
//	delete m_manifold;
//	m_manifold = nullptr;
//	CC_SAFE_DELETE(m_manifold);
}

b2Vec2 CustomContact::getContactPoint()
{
	return m_manifold.points[0];
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

//paddle
bool CustomContact::isPaddleAndFruit()
{
	b2Filter filterA = m_fixtureA->GetFilterData();
	b2Filter filterB = m_fixtureB->GetFilterData();
	if (filterA.categoryBits == (uint16)collide_bit::PADDLE
		&&filterB.categoryBits == (uint16)collide_bit::BONUS_FRUIT)
	{
		return true;
	}
	else if
		(filterB.categoryBits == (uint16)collide_bit::PADDLE
		&&filterA.categoryBits == (uint16)collide_bit::BONUS_FRUIT)
	{
		return true;
	}
	else
		return false;
}

bool CustomContact::isPaddleAndBallBonus()
{
	b2Filter filterA = m_fixtureA->GetFilterData();
	b2Filter filterB = m_fixtureB->GetFilterData();
	if (filterA.categoryBits == (uint16)collide_bit::PADDLE
		&&filterB.categoryBits == (uint16)collide_bit::BONUS_BALL)
	{
		return true;
	}
	else if
		(filterB.categoryBits == (uint16)collide_bit::PADDLE
		&&filterA.categoryBits == (uint16)collide_bit::BONUS_BALL)
	{
		return true;
	}
	else
		return false;
}
bool CustomContact::isPaddleAndUp()
{
	b2Filter filterA = m_fixtureA->GetFilterData();
	b2Filter filterB = m_fixtureB->GetFilterData();
	if (filterA.categoryBits == (uint16)collide_bit::PADDLE
		&&filterB.categoryBits == (uint16)collide_bit::BONUS_BAR_UP)
	{
		return true;
	}
	else if
		(filterB.categoryBits == (uint16)collide_bit::PADDLE
		&&filterA.categoryBits == (uint16)collide_bit::BONUS_BAR_UP)
	{
		return true;
	}
	else
		return false;
}
bool CustomContact::isPaddleAndDown()
{
	b2Filter filterA = m_fixtureA->GetFilterData();
	b2Filter filterB = m_fixtureB->GetFilterData();
	if (filterA.categoryBits == (uint16)collide_bit::PADDLE
		&&filterB.categoryBits == (uint16)collide_bit::BONUS_BAR_DOWN)
	{
		return true;
	}
	else if
		(filterB.categoryBits == (uint16)collide_bit::PADDLE
		&&filterA.categoryBits == (uint16)collide_bit::BONUS_BAR_DOWN)
	{
		return true;
	}
	else
		return false;
}
bool CustomContact::isPaddleAndSpeedUp()
{
	b2Filter filterA = m_fixtureA->GetFilterData();
	b2Filter filterB = m_fixtureB->GetFilterData();
	if (filterA.categoryBits == (uint16)collide_bit::PADDLE
		&&filterB.categoryBits == (uint16)collide_bit::BONUS_SPEED_UP)
	{
		return true;
	}
	else if
		(filterB.categoryBits == (uint16)collide_bit::PADDLE
		&&filterA.categoryBits == (uint16)collide_bit::BONUS_SPEED_UP)
	{
		return true;
	}
	else
		return false;
}
bool CustomContact::isPaddleAndSpeedDown()
{
	b2Filter filterA = m_fixtureA->GetFilterData();
	b2Filter filterB = m_fixtureB->GetFilterData();
	if (filterA.categoryBits == (uint16)collide_bit::PADDLE
		&&filterB.categoryBits == (uint16)collide_bit::BONUS_SPEED_DOWN)
	{
		return true;
	}
	else if
		(filterB.categoryBits == (uint16)collide_bit::PADDLE
		&&filterA.categoryBits == (uint16)collide_bit::BONUS_SPEED_DOWN)
	{
		return true;
	}
	else
		return false;
}
bool CustomContact::isPaddleAndQuestion()
{
	b2Filter filterA = m_fixtureA->GetFilterData();
	b2Filter filterB = m_fixtureB->GetFilterData();
	if (filterA.categoryBits == (uint16)collide_bit::PADDLE
		&&filterB.categoryBits == (uint16)collide_bit::BONUS_QUESTION)
	{
		return true;
	}
	else if
		(filterB.categoryBits == (uint16)collide_bit::PADDLE
		&&filterA.categoryBits == (uint16)collide_bit::BONUS_QUESTION)
	{
		return true;
	}
	else
		return false;
}
bool CustomContact::isPaddleAndExcalmation()
{
	b2Filter filterA = m_fixtureA->GetFilterData();
	b2Filter filterB = m_fixtureB->GetFilterData();
	if (filterA.categoryBits == (uint16)collide_bit::PADDLE
		&&filterB.categoryBits == (uint16)collide_bit::BONUS_EXCALMATION)
	{
		return true;
	}
	else if
		(filterB.categoryBits == (uint16)collide_bit::PADDLE
		&&filterA.categoryBits == (uint16)collide_bit::BONUS_EXCALMATION)
	{
		return true;
	}
	else
		return false;
}
bool CustomContact::isPaddleAndBad()
{
	b2Filter filterA = m_fixtureA->GetFilterData();
	b2Filter filterB = m_fixtureB->GetFilterData();
	if (filterA.categoryBits == (uint16)collide_bit::PADDLE
		&&filterB.categoryBits == (uint16)collide_bit::BONUS_BAD)
	{
		return true;
	}
	else if
		(filterB.categoryBits == (uint16)collide_bit::PADDLE
		&&filterA.categoryBits == (uint16)collide_bit::BONUS_BAD)
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
	else if (isPaddleAndFruit())
	{
		return collide_type::PADDLE_FRUIT;
	}
	else if (isPaddleAndBallBonus())
	{
		return collide_type::PADDLE_BALL_UP;
	}
	else if (isPaddleAndUp())
	{
		return collide_type::PADDLE_UP;
	}
	else if (isPaddleAndDown())
	{
		return collide_type::PADDLE_DOWN;
	}
	else if (isPaddleAndSpeedUp())
	{
		return collide_type::PADDLE_SPEED_UP;
	}
	else if (isPaddleAndSpeedDown())
	{
		return collide_type::PADDLE_SPEED_DOWN;
	}
	else if (isPaddleAndQuestion())
	{
		return collide_type::PADDLE_QUESTION;
	}
	else if (isPaddleAndExcalmation())
	{
		return collide_type::PADDLE_EXCALMATION;
	}
	else if (isPaddleAndBad())
	{
		return collide_type::PADDLE_BAD;
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
		CCLOG("START,%d,,,,", myContact.getCollideType());
		if (myContact.getCollideType() != collide_type::UNKNOWN)
		{
			contactVector.push_back(myContact);
			
		}
		/*if (myContact.getCollideType() == collide_type::BALL_BRICK)
		{
			CCLOG("START,%d,,,,%f,%f", myContact.getCollideType(), myContact.getContactPoint().x, myContact.getContactPoint().y);
		}*/
		
		
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
	//CCLOG("END");
}

void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	B2_NOT_USED(contact);
	B2_NOT_USED(oldManifold);
	//CCLOG("PRE");
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	B2_NOT_USED(contact);
	B2_NOT_USED(impulse);
	//CCLOG("POST");
}


std::vector<CustomContact> ContactListener::getContactVector()
{
	return contactVector;
}
