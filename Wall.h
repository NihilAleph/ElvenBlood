#pragma once
#include "Body.h"
class Wall : public Body
{
public:
	Wall();
	~Wall();

	void init(b2World* world, const glm::vec2& position, const glm::vec2& dimensions, uint16 maskBits = FixtureTag::ALL);


private:
};

