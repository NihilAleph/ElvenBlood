#include "Player.h"
#include "Box.h"
#include <SDL\SDL.h>

Player::Player()
{
}


Player::~Player()
{
}


void Player::init(b2World* world, const glm::vec2& position) {
	m_hitbox = new Box;
	glm::vec2 dimensions(1.0f, 2.5f);
	static_cast<Box*> (m_hitbox)->init(world, b2_dynamicBody, position, true, false,
		dimensions, 1.0f, 1.0f, 0.0f, false, BodyType::PLAYER, BodyType::ALL);

	m_hitbox->getBody()->SetLinearDamping(2.0f);
	m_hitbox->getBody()->SetUserData(this);

	//add foot sensor fixture
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.5f, 0.2f, b2Vec2(0, -1.25f), 0);
	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;
	fixtureDef.shape = &polygonShape;
	b2Fixture* footSensorFixture = m_hitbox->getBody()->CreateFixture(&fixtureDef);
	footSensorFixture->SetUserData((void*)3);

	m_tileSheet.init(taengine::ResourceManager::getTexture("Sprites/anya.png"), glm::ivec2(7, 1));
	m_drawDimensions = glm::vec2(3.0f, 3.0f);
}


void Player::takeDamage(float damage, b2Vec2 contactNormal) {
	//m_life -= damage;
	//contactNormal*= 0.50f;
	//m_hitbox->getBody()->ApplyLinearImpulse(contactNormal, m_hitbox->getBody()->GetPosition(), true);
}

void Player::draw(taengine::SpriteBatch& spriteBatch) {
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
	case PlayerMoveState::WALKING:
		numTiles = 4;

		m_animationTime += m_animationSpeed;

		tileIndex = (int)m_animationTime % numTiles;
		break;
	case PlayerMoveState::MIDAIR_UP:
		tileIndex = 5;
		break;
	case PlayerMoveState::MIDAIR_DOWN:
		tileIndex = 6;
		break;
	case PlayerMoveState::ATTACKING:
		tileIndex = 4;
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

void Player::update(taengine::InputManager& inputManager) {
	b2Body* body = m_hitbox->getBody();
	b2Vec2 position = body->GetPosition();

	m_moveState = PlayerMoveState::STANDING;

	if (body->GetLinearVelocity().x > 0.3f) {
		m_moveState = PlayerMoveState::WALKING;
		m_facingLeft = false;
	} else if (body->GetLinearVelocity().x < -0.3f) {
		m_moveState = PlayerMoveState::WALKING;
		m_facingLeft = true;
	}
	else {
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x * 0.9f, body->GetLinearVelocity().y));
	}

	if (body->GetLinearVelocity().y > 0.0f) {
		m_moveState = PlayerMoveState::MIDAIR_UP;
	}

	if (body->GetLinearVelocity().y < 0.0f) {
		m_moveState = PlayerMoveState::MIDAIR_DOWN;
	}

	if (inputManager.isKeyDown(SDLK_SPACE)) {
		if (m_moveState == PlayerMoveState::STANDING) {
			m_moveState = PlayerMoveState::ATTACKING;
		}
	}

	// Apply movement
	if (inputManager.isKeyDown(SDLK_d)) {
		body->ApplyForce(b2Vec2(FORCE, 0.0f), position, true);
	}
	if (inputManager.isKeyDown(SDLK_a)) {
		body->ApplyForce(b2Vec2(-FORCE, 0.0f), position, true);
	}
	if (inputManager.isKeyDown(SDLK_w)) {
		if (m_footContacts > 0) {
			body->ApplyLinearImpulse(b2Vec2(0.0f, 20.0f), position, true);
		}
	}


	// Apply air resistence
	// b2Vec2 velocity = body->GetLinearVelocity();
	// float friction = -1.0f;
	// body->ApplyForce(b2Vec2(velocity.x * friction, velocity.y * friction), position, true);
}