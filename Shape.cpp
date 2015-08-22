#include "Shape.h"


Shape::Shape()
{
}


Shape::~Shape()
{
}

void Shape::setBody(b2World* world, const b2BodyType& bodyType, const glm::vec2& position,
	const bool fixedRotation, const bool isBullet) {

	b2BodyDef bodyDef;
	bodyDef.type = bodyType;
	bodyDef.position.x = position.x;
	bodyDef.position.y = position.y;
	bodyDef.fixedRotation = fixedRotation;
	bodyDef.bullet = isBullet;

	m_body = world->CreateBody(&bodyDef);
}

b2Fixture* Shape::createFixture(const b2Shape* shape, const float density, const float friction,
	const float restitution, const bool isSensor, uint16 categoryBits, uint16 maskBits) {

	b2FixtureDef fixture;
	fixture.shape = shape;
	fixture.density = density;
	fixture.friction = friction;
	fixture.restitution = restitution;
	fixture.isSensor = isSensor;
	fixture.filter.categoryBits = categoryBits;
	fixture.filter.maskBits = maskBits;

	return m_body->CreateFixture(&fixture);
}