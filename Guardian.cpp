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
	glm::vec2 dimensions(1.5f, 4.0f);
	static_cast<Box*> (m_hitbox)->init(world, b2_dynamicBody, position, true, false,
		dimensions, 1.0f, 1.0f, 0.0f, false, BodyType::ENEMY, BodyType::ALL);

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


	if (m_hitbox) {
		b2Body* body = m_hitbox->getBody();
		m_position.x = body->GetPosition().x;
		m_position.y = body->GetPosition().y;
	}

	destRect.x = m_position.x - m_drawDimensions.x / 2;
	destRect.y = m_position.y - m_drawDimensions.x / 2;
	destRect.z = m_drawDimensions.x;
	destRect.w = m_drawDimensions.y;

	// for regular flying
	/*int tileIndex = 0;
	int numTiles = 4;

	m_animationTime += m_animationSpeed;

	tileIndex += (int)m_animationTime % numTiles;*/
	int tileIndex;

	switch (m_moveState) {
	case GuardianMoveState::DEAD:
		tileIndex = 1;
		break;
	default:
		tileIndex = 0;
	}

	uvRect = m_tileSheet.getUVs(tileIndex);

	if (m_direction == -1) {
		uvRect.x += 1.0f / m_tileSheet.dimensions.x;
		uvRect.z *= -1;
	}

	spriteBatch.draw(destRect, uvRect, 0.0f, m_tileSheet.texture.id,
		taengine::Color(255, 255, 255, 255), 0.0f);
}

void Guardian::update(taengine::InputManager& inputManager) {

	if (m_moveState == GuardianMoveState::DEAD && m_hitbox) {
		m_hitbox->getBody()->GetWorld()->DestroyBody(m_hitbox->getBody());
		m_hitbox = nullptr;
	}

	if (m_moveState == GuardianMoveState::STANDING) {
		m_counter += 1.0f / 60.0f;
		if (m_counter > m_cooldown) {
			m_counter = 0.0f;
			m_direction *= -1;
		}
	}

	// Apply air resistence
	// b2Vec2 velocity = body->GetLinearVelocity();
	// float friction = -1.0f;
	// body->ApplyForce(b2Vec2(velocity.x * friction, velocity.y * friction), position, true);
}

void Guardian::die() {

	m_moveState = GuardianMoveState::DEAD;
}


void Guardian::drawDebug(taengine::DebugRenderer& renderer, taengine::Color color) {
	if (m_hitbox) {
		m_hitbox->draw(renderer, color);
	}
}