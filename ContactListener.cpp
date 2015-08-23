#include "ContactListener.h"
#include "Body.h"
#include "Player.h"
#include "Guardian.h"

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
		// foot sensor
		if ((int)fixtureUserData == 3) {
			void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			if (static_cast<Body*>(bodyUserDataA)->getCategory() == BodyType::PLAYER) {
				static_cast<Player*>(bodyUserDataA)->addFootContacts();
			}
		}

		// attack sensor
		if ((int)fixtureUserData == 4) {
			void* bodyUserDataB = contact->GetFixtureA()->GetBody()->GetUserData();
			if (static_cast<Body*>(bodyUserDataB)->getCategory() == BodyType::ENEMY) {
				static_cast<Guardian*>(bodyUserDataB)->die();
			}
		}
	}
	//check if fixture B was the foot sensor
	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if (contact->GetFixtureB()->IsSensor()) {
		if ((int)fixtureUserData == 3) {
			void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
			if (static_cast<Body*>(bodyUserDataB)->getCategory() == BodyType::PLAYER) {
				static_cast<Player*>(bodyUserDataB)->addFootContacts();
			}
		}

		// attack sensor
		if ((int)fixtureUserData == 4) {
			void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			if (static_cast<Body*>(bodyUserDataA)->getCategory() == BodyType::ENEMY) {
				static_cast<Guardian*>(bodyUserDataA)->die();
			}
		}
	}
}

void ContactListener::EndContact(b2Contact* contact) {
	//check if fixture A was the foot sensor
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if (contact->GetFixtureA()->IsSensor()) {
		if ((int)fixtureUserData == 3) {
			void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			if (static_cast<Body*>(bodyUserDataA)->getCategory() == BodyType::PLAYER) {
				static_cast<Player*>(bodyUserDataA)->subFootContacts();
			}
		}
	}
	//check if fixture B was the foot sensor
	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if (contact->GetFixtureB()->IsSensor()) {
		if ((int)fixtureUserData == 3) {
			void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
			if (static_cast<Body*>(bodyUserDataB)->getCategory() == BodyType::PLAYER) {
				static_cast<Player*>(bodyUserDataB)->subFootContacts();
			}
		}
	}
}