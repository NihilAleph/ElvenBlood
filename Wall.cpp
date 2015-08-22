#include "Wall.h"
#include "Box.h"

Wall::Wall()
{
}


Wall::~Wall()
{
}


void Wall::init(b2World* world, const glm::vec2& position, const glm::vec2& dimensions, uint16 maskBits) {
	m_hitbox = new Box;
	static_cast<Box*>(m_hitbox)->init(world, b2_staticBody, position, true, false, dimensions,
		1.0f, 0.0f, 0.0f, false, BodyType::WALL, maskBits);

}
