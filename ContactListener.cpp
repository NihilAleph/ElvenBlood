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
	uint16 fixtureCategoryA = contact->GetFixtureA()->GetFilterData().categoryBits;
	uint16 fixtureCategoryB = contact->GetFixtureB()->GetFilterData().categoryBits;
	if (contact->GetFixtureA()->IsSensor()) {
		// foot sensor
		if (fixtureCategoryA == FixtureTag::PLAYER_FOOT) {
			void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			static_cast<Player*>(bodyUserDataA)->addFootContacts();
			if (fixtureCategoryB == FixtureTag::ENEMY_BODY) {

				void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
				static_cast<Guardian*>(bodyUserDataB)->foundAnya();
				static_cast<Player*>(bodyUserDataA)->setSighted();
			}
			
		}

		// attack sensor
		if (fixtureCategoryA == FixtureTag::PLAYER_KNIFE) {
			void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
			static_cast<Guardian*>(bodyUserDataB)->die();
			void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			static_cast<Player*>(bodyUserDataA)->addKill();
		}

		// sight sensor
		if (fixtureCategoryA == FixtureTag::ENEMY_SIGHT) {
			void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			static_cast<Guardian*>(bodyUserDataA)->foundAnya();

			void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
			static_cast<Player*>(bodyUserDataB)->setSighted();
		}

		// Finish Sensor
		if (fixtureCategoryA == FixtureTag::SENSOR) {

			void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
			static_cast<Player*>(bodyUserDataB)->escaped();
		}
	}

	//check if fixture B was the foot sensor
	if (contact->GetFixtureB()->IsSensor()) {
		if (fixtureCategoryB == FixtureTag::PLAYER_FOOT) {
			void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
			static_cast<Player*>(bodyUserDataB)->addFootContacts();
			if (fixtureCategoryA == FixtureTag::ENEMY_BODY) {

				void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
				static_cast<Guardian*>(bodyUserDataA)->foundAnya();
				static_cast<Player*>(bodyUserDataB)->setSighted();
			}
		}

		// attack sensor
		if (fixtureCategoryB == FixtureTag::PLAYER_KNIFE) {
			void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			static_cast<Guardian*>(bodyUserDataA)->die();
			void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
			static_cast<Player*>(bodyUserDataB)->addKill();
			
		}

		// sight sensor
		if (fixtureCategoryB == FixtureTag::ENEMY_SIGHT) {
			void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
			static_cast<Guardian*>(bodyUserDataB)->foundAnya();

			void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			static_cast<Player*>(bodyUserDataA)->setSighted();
		}


		// Finish Sensor
		if (fixtureCategoryB == FixtureTag::SENSOR) {
			void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			static_cast<Player*>(bodyUserDataA)->escaped();
		}
	}
}

void ContactListener::EndContact(b2Contact* contact) {
	//check if fixture A was the foot sensor
	uint16 fixtureCategoryA = contact->GetFixtureA()->GetFilterData().categoryBits;
	uint16 fixtureCategoryB = contact->GetFixtureB()->GetFilterData().categoryBits;

	if (contact->GetFixtureA()->IsSensor()) {
		if (fixtureCategoryA == FixtureTag::PLAYER_FOOT) {
			void* bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
			static_cast<Player*>(bodyUserDataA)->subFootContacts();
			
		}
	}
	//check if fixture B was the foot sensor
	if (contact->GetFixtureB()->IsSensor()) {
		if (fixtureCategoryB == FixtureTag::PLAYER_FOOT) {
			void* bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();
			static_cast<Player*>(bodyUserDataB)->subFootContacts();
			
		}
	}
}