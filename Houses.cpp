#include "Houses.h"
#include <taengine\ResourceManager.h>

Houses::Houses()
{
}


Houses::~Houses()
{
}


void Houses::init() {

	m_tileSheet.init(taengine::ResourceManager::getTexture("Sprites/houses.png"), glm::ivec2(3, 1));
	m_drawDimensions = glm::vec2(120.0f, 30.0f);
}

void Houses::draw(taengine::SpriteBatch& spriteBatch) {
	glm::vec4 destRect;
	destRect.x = -14.0f;
	destRect.y = -10;
	destRect.z = m_drawDimensions.x;
	destRect.w = m_drawDimensions.y;

	glm::vec4 uvRect;

	int tileIndex = 0;
	int numTiles = 3;

	tileIndex = (int) m_animationTime % numTiles;

	uvRect = m_tileSheet.getUVs(tileIndex);

	m_animationTime += 0.2f;

	spriteBatch.draw(destRect, uvRect, -10.0f, m_tileSheet.texture.id,
		taengine::Color(255, 255, 255, 255));
}