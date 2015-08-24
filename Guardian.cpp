#include "Guardian.h"
#include "Box.h"
#include <SDL\SDL.h>
#include <random>
#include <ctime>

Guardian::Guardian()
{
}


Guardian::~Guardian()
{
}


void Guardian::init(b2World* world, const glm::vec2& position, float cooldown, float range, int direction, taengine::SoundEffect killEffect) {
	m_hitbox = new Box;
	glm::vec2 dimensions(1.5f, 4.0f);
	static_cast<Box*> (m_hitbox)->init(world, b2_staticBody, position, true, false,
		dimensions, 1.0f, 1.0f, 0.0f, false, FixtureTag::ENEMY_BODY, FixtureTag::ALL);

	m_hitbox->getBody()->SetLinearDamping(2.0f);
	m_hitbox->getBody()->SetUserData(this);

	m_cooldown = cooldown;
	m_counter = 0.0f;
	m_range = range;
	m_direction = direction;

	m_killEffect = killEffect;

	bool m_foundAnya = false;

	//add sight sensor fixture
	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(m_range, 2.0f, b2Vec2((-m_range - 0.75f) * m_direction, 0.0f), 0);
	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;
	fixtureDef.shape = &polygonShape;
	fixtureDef.filter.categoryBits = FixtureTag::ENEMY_SIGHT;
	fixtureDef.filter.maskBits = FixtureTag::PLAYER_BODY;
	m_sightSensor = m_hitbox->getBody()->CreateFixture(&fixtureDef);

	m_tileSheet.init(taengine::ResourceManager::getTexture("Sprites/guardian.png"), glm::ivec2(2, 1));
	m_drawDimensions = glm::vec2(4.5f, 4.5f);

	m_moveState = GuardianMoveState::STANDING;
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
		taengine::Color(128, 128, 128, 255), 0.0f);
}

void Guardian::update(taengine::InputManager& inputManager) {

	if (m_hitbox) {
		if (m_moveState == GuardianMoveState::DEAD) {
			m_hitbox->getBody()->GetWorld()->DestroyBody(m_hitbox->getBody());
			m_hitbox = nullptr;
		}

		if (m_moveState == GuardianMoveState::STANDING && m_cooldown > 0) {
			m_counter += 1.0f / 60.0f;
			if (m_counter > m_cooldown) {
				m_counter = 0.0f;
				m_direction *= -1;

				m_hitbox->getBody()->DestroyFixture(m_sightSensor);

				//add sight sensor fixture
				b2PolygonShape polygonShape;
				polygonShape.SetAsBox(m_range, 2.0f, b2Vec2((-m_range - 0.75f) * m_direction, 0.0f), 0);
				b2FixtureDef fixtureDef;
				fixtureDef.isSensor = true;
				fixtureDef.shape = &polygonShape;
				fixtureDef.filter.categoryBits = FixtureTag::ENEMY_SIGHT;
				fixtureDef.filter.maskBits = FixtureTag::PLAYER_BODY;
				m_sightSensor = m_hitbox->getBody()->CreateFixture(&fixtureDef);
			}
		}
	}

}

void Guardian::die() {
	m_moveState = GuardianMoveState::DEAD;
	m_killEffect.play();
}


void Guardian::drawDebug(taengine::DebugRenderer& renderer, taengine::Color color) {
	if (m_hitbox) {
		m_hitbox->draw(renderer, color);

		glm::vec4 destRect;
		if (m_direction > 0) {
			destRect.x = m_hitbox->getBody()->GetPosition().x - (0.75f + 2 * m_range);
		}
		else {
			destRect.x = m_hitbox->getBody()->GetPosition().x + (0.75f);

		}
		destRect.y = m_hitbox->getBody()->GetPosition().y - 2.0f;
		destRect.z = 10.0f;
		destRect.w = 4.0f;

		renderer.drawBox(destRect, color, 0.0f);
	}
}

void Guardian::drawLight(taengine::SpriteBatch& spriteBatch) {

	// extreme go horse
	if (m_hitbox) {
		glm::vec4 destRect;
		destRect.x = m_position.x - m_range * 4 / 2.0f - 0.75f;
		destRect.y = m_position.y - m_range * 4 / 2.0f;
		destRect.z = m_range * 4 + 1.5f;
		destRect.w = m_range * 4;
			
		glm::vec4 uvRect(-1.0f, -1.0f, 2.0f, 2.0f);
		uvRect *= -m_direction;

		spriteBatch.draw(destRect, uvRect, 0.0f, 0, taengine::Color(155, 155, 0, 255));
	}
}

void Guardian::foundAnya()  {

	// Make a bunch of boxes
	std::mt19937 randGenerator(time(nullptr));
	std::uniform_int_distribution<int> number(0, 5);


	m_shoutNumber = number(randGenerator);

	m_foundAnya = true;
}

std::string Guardian::shout() {
	return shouts[m_shoutNumber];
}