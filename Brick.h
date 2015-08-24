#pragma once
#include "Body.h"

class Brick : public Body
{
public:
	Brick();
	~Brick();
	void init(b2World* world, const glm::vec2& position, uint16 maskBits = FixtureTag::ALL);

	void draw(taengine::SpriteBatch& spriteBatch);
	void drawDebug(taengine::DebugRenderer& debugRenderer, taengine::Color color);
};

