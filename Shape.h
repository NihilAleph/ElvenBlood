#pragma once
#include <taengine\DebugRenderer.h>
#include <Box2D\Box2D.h>
#include <glm\glm.hpp>

class Shape
{
public:
	Shape();
	~Shape();

	virtual void draw(taengine::DebugRenderer& renderer, taengine::Color color) = 0;

	b2Body* getBody() { return m_body; }

protected:
	b2Body* m_body;

	void setBody(b2World* world, const b2BodyType& bodyType, const glm::vec2& position,
		const bool fixedRotation, const bool isBullet);
	b2Fixture* createFixture(const b2Shape* shape, const float density, const float friction,
		const float restitution, const bool isSensor, uint16 categoryBits, uint16 maskBits);
};

