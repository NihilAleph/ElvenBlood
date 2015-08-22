#pragma once
#include "Shape.h"
#include <taengine\TileSheet.h>
#include <taengine\GLTexture.h>
#include <taengine\SpriteBatch.h>
#include <taengine\InputManager.h>
#include <taengine\ResourceManager.h>
enum BodyType {
	PLAYER = 0x0001,
	ENEMY = 0x0002,
	WALL = 0x0004,
	BOUNDARY = 0x0010,
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

	const float GRAVITY = 9.81f;


	virtual void draw(taengine::SpriteBatch& spriteBatch) {};
	virtual void update(taengine::InputManager& inputManager) {};
	virtual int getCategory() = 0;

protected:
	Shape* m_hitbox;

	taengine::TileSheet m_tileSheet;
	glm::vec2 m_drawDimensions;

};

