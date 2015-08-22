#pragma once
#include <taengine\TileSheet.h>
#include <taengine\SpriteBatch.h>
class Background
{
public:
	Background();
	~Background();

	void init();
	void draw(taengine::SpriteBatch& spriteBatch);

private:
	taengine::TileSheet m_tileSheet;
	glm::vec2 m_drawDimensions;
	glm::vec2 m_uv;
};

