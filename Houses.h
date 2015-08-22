#pragma once
#include <taengine\TileSheet.h>
#include <taengine\SpriteBatch.h>
class Houses
{
public:
	Houses();
	~Houses();

	void init();
	void draw(taengine::SpriteBatch& spriteBatch);

private:
	taengine::TileSheet m_tileSheet;
	glm::vec2 m_drawDimensions;
	glm::vec2 m_uv;

	float m_animationTime = 0.0f;
};

