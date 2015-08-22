#include "ContactListener.h"
#include "Body.h"
#include "Player.h"

ContactListener::ContactListener()
{
}


ContactListener::~ContactListener()
{
}



void ContactListener::BeginContact(b2Contact* contact) {
	//check if fixture A was the foot sensor
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if (contact->GetFixtureA()->IsSensor()) {
		void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		if (static_cast<Body*>(bodyUserDataA)->getCategory() == BodyType::PLAYER) {
			static_cast<Player*>(bodyUserDataA)->addFootContacts();
		}
	}
	//check if fixture B was the foot sensor
	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if (contact->GetFixtureB()->IsSensor()) {
		void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
		if (static_cast<Body*>(bodyUserDataB)->getCategory() == BodyType::PLAYER) {
			static_cast<Player*>(bodyUserDataB)->addFootContacts();
		}
	}
}

void ContactListener::EndContact(b2Contact* contact) {
	//check if fixture A was the foot sensor
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if (contact->GetFixtureA()->IsSensor()) {
		void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		if (static_cast<Body*>(bodyUserDataA)->getCategory() == BodyType::PLAYER) {
			static_cast<Player*>(bodyUserDataA)->subFootContacts();
		}
	}
	//check if fixture B was the foot sensor
	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if (contact->GetFixtureB()->IsSensor()) {
		void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
		if (static_cast<Body*>(bodyUserDataB)->getCategory() == BodyType::PLAYER) {
			static_cast<Player*>(bodyUserDataB)->subFootContacts();
		}
	}
}