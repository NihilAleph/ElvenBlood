#include "Sensor.h"
#include "Box.h"

Sensor::Sensor()
{
}


Sensor::~Sensor()
{
}


void Sensor::init(b2World* world, const glm::vec2& position, const glm::vec2& dimensions, uint16 maskBits) {
	m_hitbox = new Box;
	static_cast<Box*>(m_hitbox)->init(world, b2_staticBody, position, true, false, dimensions,
		1.0f, 0.0f, 0.0f, true, FixtureTag::SENSOR, maskBits);

}
