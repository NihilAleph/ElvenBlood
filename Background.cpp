#include "Background.h"
#include <taengine\ResourceManager.h>

Background::Background()
{
}


Background::~Background()
{
}


void Background::init() {

	m_tileSheet.init(taengine::ResourceManager::getTexture("Sprites/city.png"), glm::ivec2(1, 1));
	m_drawDimensions = glm::vec2(60.0f, 20.0f);
	m_uv = glm::vec2(0.0f, 0.0f);
}

void Background::draw(taengine::SpriteBatch& spriteBatch) {
	glm::vec4 destRect;
	destRect.x = - 14.0f;
	destRect.y = -m_drawDimensions.y / 2.0f;
	destRect.z = m_drawDimensions.x;
	destRect.w = m_drawDimensions.y;

	glm::vec4 uvRect;

	uvRect.x = m_uv.x;
	uvRect.y = m_uv.y;
	uvRect.z = 1.0f;
	uvRect.w = 1.0f;

	spriteBatch.draw(destRect, uvRect, -10.0f, m_tileSheet.texture.id,
		taengine::Color(255, 255, 255, 255));
}