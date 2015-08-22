#include "Guardian.h"
#include "Box.h"
#include <SDL\SDL.h>

Guardian::Guardian()
{
}


Guardian::~Guardian()
{
}


void Guardian::init(b2World* world, const glm::vec2& position) {
	m_hitbox = new Box;
	glm::vec2 dimensions(1.0f, 3.5f);
	static_cast<Box*> (m_hitbox)->init(world, b2_dynamicBody, position, true, false,
		dimensions, 1.0f, 1.0f, 0.0f, false, BodyType::PLAYER, BodyType::ALL);

	m_hitbox->getBody()->SetLinearDamping(2.0f);
	m_hitbox->getBody()->SetUserData(this);

	//add foot sensor fixture
	//b2PolygonShape polygonShape;
	//polygonShape.SetAsBox(0.5f, 0.2f, b2Vec2(0, -1.25f), 0);
	//b2FixtureDef fixtureDef;
	//fixtureDef.isSensor = true;
	//fixtureDef.shape = &polygonShape;
	//b2Fixture* footSensorFixture = m_hitbox->getBody()->CreateFixture(&fixtureDef);
	//footSensorFixture->SetUserData((void*)3);

	m_tileSheet.init(taengine::ResourceManager::getTexture("Sprites/guardian.png"), glm::ivec2(2, 1));
	m_drawDimensions = glm::vec2(4.5f, 4.5f);
}

void Guardian::draw(taengine::SpriteBatch& spriteBatch) {
	glm::vec4 destRect;
	glm::vec4 uvRect;

	b2Body* body = m_hitbox->getBody();

	destRect.x = body->GetPosition().x - m_drawDimensions.x / 2;
	destRect.y = body->GetPosition().y - m_drawDimensions.x / 2;
	destRect.z = m_drawDimensions.x;
	destRect.w = m_drawDimensions.y;

	// for regular flying
	/*int tileIndex = 0;
	int numTiles = 4;

	m_animationTime += m_animationSpeed;

	tileIndex += (int)m_animationTime % numTiles;*/
	int tileIndex = 0;
	int numTiles = 0;

	switch (m_moveState) {
	case GuardianMoveState::DEAD:
		tileIndex = 1;
		break;
	default:
		m_animationTime = 0;

	}

	uvRect = m_tileSheet.getUVs(tileIndex);

	if (m_facingLeft) {
		uvRect.x += 1.0f / m_tileSheet.dimensions.x;
		uvRect.z *= -1;
	}

	spriteBatch.draw(destRect, uvRect, 0.0f, m_tileSheet.texture.id,
		taengine::Color(255, 255, 255, 255), body->GetAngle());
}

void Guardian::update(taengine::InputManager& inputManager) {
	b2Body* body = m_hitbox->getBody();
	b2Vec2 position = body->GetPosition();

	m_moveState = GuardianMoveState::STANDING;

	// Apply air resistence
	// b2Vec2 velocity = body->GetLinearVelocity();
	// float friction = -1.0f;
	// body->ApplyForce(b2Vec2(velocity.x * friction, velocity.y * friction), position, true);
}