#pragma once
#include "Shape.h"
class Box : public Shape
{
public:
	Box();
	~Box();

	void init(b2World* world, const b2BodyType bodyType, const glm::vec2& position,
		bool fixedRotation, bool isBullet, const glm::vec2 dimensions, float density, float friction,
		float restitution, bool isSensor, uint16 categoryBits, uint16 maskBits);
	virtual void draw(taengine::DebugRenderer& renderer, taengine::Color color) override;

	glm::vec2 getRadius() { return m_dimensions; }

private:
	glm::vec2 m_dimensions;
};

