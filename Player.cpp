#include "Player.h"
#include "Box.h"
#include <SDL\SDL.h>

Player::Player()
{
}


Player::~Player()
{
}


void Player::init(b2World* world, const glm::vec2& position, taengine::SoundEffect jumpEffect) {
	m_hitbox = new Box;
	glm::vec2 dimensions(1.0f, 2.5f);
	static_cast<Box*> (m_hitbox)->init(world, b2_dynamicBody, position, true, false,
		dimensions, 1.0f, 1.0f, 0.0f, false, FixtureTag::PLAYER_BODY, FixtureTag::ALL);

	m_hitbox->getBody()->SetLinearDamping(2.0f);
	m_hitbox->getBody()->SetUserData(this);

	//add foot sensor fixture
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(0.45f, 0.2f, b2Vec2(0, -1.25f), 0);
	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;
	fixtureDef.shape = &polygonShape;
	fixtureDef.filter.categoryBits = FixtureTag::PLAYER_FOOT;
	fixtureDef.filter.maskBits = FixtureTag::WALL | FixtureTag::ENEMY_BODY;
	b2Fixture* footSensorFixture = m_hitbox->getBody()->CreateFixture(&fixtureDef);
	footSensorFixture->SetUserData((void*)3);

	m_tileSheet.init(taengine::ResourceManager::getTexture("Sprites/anya.png"), glm::ivec2(7, 4));
	m_drawDimensions = glm::vec2(3.0f, 3.0f);

	m_jumpEffect = jumpEffect;

	m_animationSpeed = 0.15f;
	m_animationTime = 0.0f;

	m_direction = 1;

	m_footContacts = 0;

	m_killCount = 0;
	m_escaped = false;
	m_moveState = PlayerMoveState::STANDING;
}

void Player::draw(taengine::SpriteBatch& spriteBatch) {
	glm::vec4 destRect;
	glm::vec4 uvRect;

	b2Body* body = m_hitbox->getBody();

	destRect.x = body->GetPosition().x - m_drawDimensions.x / 2 - 0.1f;
	destRect.y = body->GetPosition().y - m_drawDimensions.x / 2;
	destRect.z = m_drawDimensions.x;
	destRect.w = m_drawDimensions.y;

	// for regular flying
	/*int tileIndex = 0;
	int numTiles = 4;

	m_animationTime += m_animationSpeed;

	tileIndex += (int)m_animationTime % numTiles;*/
	int tileRow = 0;
	if (m_killCount < 1) {
		tileRow = 3;
	}
	else if (m_killCount < 3) {
		tileRow = 2;
	}
	else if (m_killCount < 5) {
		tileRow = 1;
	}
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
	tileIndex += tileRow * 7;

	uvRect = m_tileSheet.getUVs(tileIndex);

	if (m_direction == -1) {
		uvRect.x += 1.0f / m_tileSheet.dimensions.x;
		uvRect.z *= -1;
	}

	spriteBatch.draw(destRect, uvRect, 1.0f, m_tileSheet.texture.id,
		taengine::Color(155, 155, 155, 255), body->GetAngle());
}

void Player::update(taengine::InputManager& inputManager) {

	const float FORCE = 25.0f;

	b2Body* body = m_hitbox->getBody();
	b2Vec2 position = body->GetPosition();

	// Eliminate any attack sensor
	if (m_attackSensor) {
		body->DestroyFixture(m_attackSensor);
		m_attackSensor = nullptr;
	}

	m_moveState = PlayerMoveState::STANDING;

	if (body->GetLinearVelocity().x > 0.3f) {
		m_moveState = PlayerMoveState::WALKING;
		m_direction = 1;
	} else if (body->GetLinearVelocity().x < -0.3f) {
		m_moveState = PlayerMoveState::WALKING;
		m_direction = -1;
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

			//add attack sensor fixture
			b2PolygonShape polygonShape;
			polygonShape.SetAsBox(1.0f, 0.2f, b2Vec2(0.9f * m_direction, -0.1f), 0);
			b2FixtureDef fixtureDef;
			fixtureDef.isSensor = true;
			fixtureDef.shape = &polygonShape;
			fixtureDef.filter.categoryBits = FixtureTag::PLAYER_KNIFE;
			fixtureDef.filter.maskBits = FixtureTag::ENEMY_BODY;
			m_attackSensor = m_hitbox->getBody()->CreateFixture(&fixtureDef);
			m_attackSensor->SetUserData((void*)4);
		}
	}

	// Apply movement
	if (inputManager.isKeyDown(SDLK_d)) {
		body->ApplyForce(b2Vec2(FORCE, 0.0f), position, true);
	}
	if (inputManager.isKeyDown(SDLK_a)) {
		body->ApplyForce(b2Vec2(-FORCE, 0.0f), position, true);
	}
	if (inputManager.isKeyPressed(SDLK_w)) {
		if (m_footContacts > 0) {
			m_jumpEffect.play();
			body->ApplyLinearImpulse(b2Vec2(0.0f, 45.0f), position, true);
		}
	}


	// Apply air resistence
	// b2Vec2 velocity = body->GetLinearVelocity();
	// float friction = -1.0f;
	// body->ApplyForce(b2Vec2(velocity.x * friction, velocity.y * friction), position, true);
}


void Player::drawDebug(taengine::DebugRenderer& renderer, taengine::Color color) {
	m_hitbox->draw(renderer, color);

	if (m_attackSensor) {

		glm::vec4 destRect;
		destRect.x = m_hitbox->getBody()->GetPosition().x + 0.9f * m_direction - 0.5f;
		destRect.y = m_hitbox->getBody()->GetPosition().y - 0.2f;
		destRect.z = 1.0f;
		destRect.w = 0.2f;

		renderer.drawBox(destRect, color, 0.0f);
	}
}