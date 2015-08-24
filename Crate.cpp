#include "Crate.h"
#include "Box.h"

Crate::Crate()
{
}


Crate::~Crate()
{
}


void Crate::init(b2World* world, const glm::vec2& position, uint16 maskBits) {
	m_hitbox = new Box;
	glm::vec2 dimensions(2.25f, 2.5f);
	static_cast<Box*>(m_hitbox)->init(world, b2_staticBody, position, true, false, dimensions,
		1.0f, 0.0f, 0.0f, false, FixtureTag::WALL, maskBits);

	m_tileSheet.init(taengine::ResourceManager::getTexture("Sprites/crate1.png"), glm::ivec2(1, 1));
	m_drawDimensions = glm::vec2(3.0f, 3.0f);
}



void Crate::draw(taengine::SpriteBatch& spriteBatch) {
	glm::vec4 destRect;
	b2Body* body = m_hitbox->getBody();

	destRect.x = body->GetPosition().x - m_drawDimensions.x / 2 - 0.25;
	destRect.y = body->GetPosition().y - m_drawDimensions.y / 2;
	destRect.z = m_drawDimensions.x;
	destRect.w = m_drawDimensions.y;

	glm::vec4 uvRect = m_tileSheet.getUVs(0);


	spriteBatch.draw(destRect, uvRect, -0.5f, m_tileSheet.texture.id,
		taengine::Color(128, 128, 128, 255));
}

void Crate::drawDebug(taengine::DebugRenderer& debugRender, taengine::Color color) {
	m_hitbox->draw(debugRender, color);
}