#include "Body.h"


Body::Body()
{
}


Body::~Body()
{
}

void Body::drawDebug(taengine::DebugRenderer& renderer, taengine::Color color) {
	m_hitbox->draw(renderer, color);
}
