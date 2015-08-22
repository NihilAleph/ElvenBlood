#pragma once
#include "Body.h"

enum class EnemyMoveState { STANDING, WALKING, DEAD };

class Guardian : public Body
{
public:
	Guardian();
	~Guardian();

	virtual void init(b2World* world, const glm::vec2& position) override;

	virtual void draw(taengine::SpriteBatch& spriteBatch) override;
	virtual void update(taengine::InputManager& inputManager) override;
	virtual int getCategory() override {
		return BodyType::ENEMY;
	}

private:

	float m_animationSpeed = 0.15f;
	float m_animationTime = 0.0f;

	bool m_facingLeft = false;

	int m_footContacts = 0;

	EnemyMoveState m_moveState = EnemyMoveState::STANDING;
};

