#pragma once
#include "Body.h"
#include <taengine\AudioEngine.h>

enum class PlayerMoveState { STANDING, WALKING, ATTACKING, MIDAIR_UP, MIDAIR_DOWN, SIGHTED, ESCAPED };

class Player : public Body
{
public:
	Player();
	~Player();

	void init(b2World* world, const glm::vec2& position, taengine::SoundEffect jumpEffect) ;

	virtual void draw(taengine::SpriteBatch& spriteBatch) override;
	virtual void update(taengine::InputManager& inputManager) override;

	void drawDebug(taengine::DebugRenderer& renderer, taengine::Color color);

	void addFootContacts() { m_footContacts++; }
	void subFootContacts() { m_footContacts--; }

	void addKill() { m_killCount++; }
	int getKillCount() { return m_killCount; }

	void setSighted() { m_moveState = PlayerMoveState::SIGHTED; }
	bool isSighted() { return m_moveState == PlayerMoveState::SIGHTED; }

	void escaped() { m_moveState = PlayerMoveState::ESCAPED;
	}
	bool hasEscaped() { return m_moveState == PlayerMoveState::ESCAPED; }

private:

	float m_animationSpeed = 0.15f;
	float m_animationTime = 0.0f;

	int m_direction = 1; // or -1

	int m_footContacts = 0;

	int m_killCount = 0;

	PlayerMoveState m_moveState;

	b2Fixture* m_attackSensor = nullptr;

	taengine::SoundEffect m_jumpEffect;
};

