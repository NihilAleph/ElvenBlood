#include "Box.h"


Box::Box()
{
}


Box::~Box()
{
}

void Box::init(b2World* world, const b2BodyType bodyType, const glm::vec2& position,
	bool fixedRotation, bool isBullet, const glm::vec2 dimensions, float density, float friction,
	float restitution, bool isSensor, uint16 categoryBits, uint16 maskBits) {

	m_dimensions = dimensions;

	setBody(world, bodyType, position, fixedRotation, isBullet);

	b2PolygonShape shape;
	shape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);

	createFixture(&shape, density, friction, restitution, isSensor, categoryBits, maskBits);
}

void Box::draw(taengine::DebugRenderer& renderer, taengine::Color color) {
	glm::vec4 destRect;
	destRect.x = m_body->GetPosition().x - m_dimensions.x / 2.0f;
	destRect.y = m_body->GetPosition().y - m_dimensions.y / 2.0f;
	destRect.z = m_dimensions.x;
	destRect.w = m_dimensions.y;

	renderer.drawBox(destRect, color, m_body->GetAngle());
}
