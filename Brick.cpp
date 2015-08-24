#include "Brick.h"
#include "Box.h"

Brick::Brick()
{
}


Brick::~Brick()
{
}


void Brick::init(b2World* world, const glm::vec2& position, uint16 maskBits) {
	m_hitbox = new Box;
	glm::vec2 dimensions(1.00f, 0.75f);
	static_cast<Box*>(m_hitbox)->init(world, b2_staticBody, position, true, false, dimensions,
		1.0f, 0.0f, 0.0f, false, FixtureTag::WALL, maskBits);

	m_tileSheet.init(taengine::ResourceManager::getTexture("Sprites/brick.png"), glm::ivec2(1, 1));
	m_drawDimensions = glm::vec2(1.5f, 0.75f);
}



void Brick::draw(taengine::SpriteBatch& spriteBatch) {
	glm::vec4 destRect;
	b2Body* body = m_hitbox->getBody();

	destRect.x = body->GetPosition().x - m_drawDimensions.x / 2;
	destRect.y = body->GetPosition().y - m_drawDimensions.y / 2;
	destRect.z = m_drawDimensions.x;
	destRect.w = m_drawDimensions.y;

	glm::vec4 uvRect = m_tileSheet.getUVs(0);


	spriteBatch.draw(destRect, uvRect, -1.0f, m_tileSheet.texture.id,
		taengine::Color(128, 128, 128, 255));
}

void Brick::drawDebug(taengine::DebugRenderer& debugRender, taengine::Color color) {
	m_hitbox->draw(debugRender, color);
}