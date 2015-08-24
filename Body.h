#pragma once
#include "Shape.h"
#include <taengine\TileSheet.h>
#include <taengine\GLTexture.h>
#include <taengine\SpriteBatch.h>
#include <taengine\InputManager.h>
#include <taengine\ResourceManager.h>
enum FixtureTag {
	PLAYER_BODY = 0x0001,
	PLAYER_KNIFE = 0x0002,
	PLAYER_FOOT = 0x0004,
	ENEMY_BODY = 0x0008,
	ENEMY_SIGHT = 0x0010,
	WALL = 0x0020,
	SENSOR = 0x0040,
	ALL = 0XFFFF
};

class Body
{
public:
	Body();
	~Body();

	virtual void init(b2World* world, const glm::vec2& position) {};

	void drawDebug(taengine::DebugRenderer& renderer, taengine::Color color);

	const glm::vec2 getPosition() {
		return glm::vec2(m_hitbox->getBody()->GetPosition().x, m_hitbox->getBody()->GetPosition().y);
	}

	virtual void draw(taengine::SpriteBatch& spriteBatch) {};
	virtual void update(taengine::InputManager& inputManager) {};

protected:
	Shape* m_hitbox;

	taengine::TileSheet m_tileSheet;
	glm::vec2 m_drawDimensions;

};

