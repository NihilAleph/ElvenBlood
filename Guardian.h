#pragma once
#include "Body.h"
#include <taengine\AudioEngine.h>

enum class GuardianMoveState { STANDING, WALKING, DEAD };
static std::string shouts[] = {"I got you now, you little monster!", "Where do you think you're going, little elf?",
								"There she is! Grab that beast!", "There is one trying to escape! Grab her!",
								"Look, another monster! Kill her!", "Freeze, you scum! Drop your knife!" };

class Guardian : public Body
{
public:
	Guardian();
	~Guardian();

	void init(b2World* world, const glm::vec2& position, float cooldown, float range, int direction, taengine::SoundEffect killEffect);

	virtual void draw(taengine::SpriteBatch& spriteBatch) override;
	void drawLight(taengine::SpriteBatch& spriteBatch);
	virtual void update(taengine::InputManager& inputManager) override;
	void drawDebug(taengine::DebugRenderer& renderer, taengine::Color color);

	void setCounter(float counter) { m_counter = counter; }
	void foundAnya();
	bool hasFoundAnya() { return m_foundAnya; }

	std::string shout();

	void die();

private:

	float m_cooldown = 5.0f;
	float m_counter = 0.0f;
	float m_range = 5.0f;

	int m_direction = 1; // ou -1

	bool m_foundAnya = false;
	int m_shoutNumber;

	glm::vec2 m_position;

	GuardianMoveState m_moveState;

	b2Fixture* m_sightSensor;

	taengine::SoundEffect m_killEffect;
};

