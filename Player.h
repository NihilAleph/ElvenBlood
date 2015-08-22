#pragma once
#include "Body.h"

enum class PlayerMoveState { STANDING, WALKING, ATTACKING, MIDAIR_UP, MIDAIR_DOWN };

class Player : public Body
{
public:
	Player();
	~Player();

	void takeDamage(float damage, b2Vec2 contactNormal);

	virtual void init(b2World* world, const glm::vec2& position) override;

	virtual void draw(taengine::SpriteBatch& spriteBatch) override;
	virtual void update(taengine::InputManager& inputManager) override;
	virtual int getCategory() override {
		return BodyType::PLAYER;
	}
	const float FORCE = 20.0f;

private:

	float m_animationSpeed = 0.15f;
	float m_animationTime = 0.0f;

	bool m_facingLeft = false;

	PlayerMoveState m_moveState = PlayerMoveState::STANDING;
};

