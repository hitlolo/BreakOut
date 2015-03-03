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

//----------------------------------------------------------
//----------------------------------------------------------

void ContactListener::BeginContact(b2Contact* contact)  // Called when two fixtures begin to touch.
{
	if (contact)
	{
		CustomContact myContact(contact);
		contactVector.push_back(myContact);
		b2Filter filter =  contact->GetFixtureA()->GetFilterData();
		
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
