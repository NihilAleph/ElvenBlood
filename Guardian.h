#pragma once
#include "Body.h"

enum class GuardianMoveState { STANDING, WALKING, DEAD };

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
	void drawDebug(taengine::DebugRenderer& renderer, taengine::Color color);

	void die();

private:

	float m_cooldown = 3.0f;
	float m_counter = 0.0f;

	int m_direction = 1; // ou -1

	glm::vec2 m_position;

	GuardianMoveState m_moveState = GuardianMoveState::STANDING;

};

