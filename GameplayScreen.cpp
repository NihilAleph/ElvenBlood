#include "GameplayScreen.h"
#include <taengine/IMainGame.h>
#include <taengine\ResourceManager.h>
#include <iostream>

GameplayScreen::GameplayScreen(taengine::Window* window) : m_window(window)
{
}


GameplayScreen::~GameplayScreen()
{
}


void GameplayScreen::build() {

}

void GameplayScreen::destroy() {

}

void GameplayScreen::onEntry() {

	m_spriteBatch.init();
	m_spriteFont = new taengine::SpriteFont("Fonts/OpenSans-Regular.ttf", 64);

	m_hudSpriteBatch.init();

	m_renderDebug = true;
	m_debugRenderer.init();

	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");

	m_textureProgram.linkShaders();

	// Compile light shader
	m_lightProgram.compileShaders("Shaders/lightShading.vert", "Shaders/lightShading.frag");

	m_lightProgram.addAttribute("vertexPositon");
	m_lightProgram.addAttribute("vertexColor");
	m_lightProgram.addAttribute("vertexUV");

	m_lightProgram.linkShaders();

	m_gameState = GameState::LOAD;
}

void GameplayScreen::loadLevel() {

	// init of the game

	b2Vec2 gravity(0.0f, -20.0f);
	m_world = std::make_unique<b2World>(gravity);
	m_world.get()->SetContactListener(&m_contactListener);

	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());

	m_camera.setPosition(glm::vec2(0.0f, 0.0f));
	m_camera.setScale(32.0f);

	m_hudCamera.init(m_window->getScreenWidth(), m_window->getScreenHeight());
	m_hudCamera.setPosition(glm::vec2(m_window->getScreenWidth() / 2.0f, m_window->getScreenHeight() / 2.0f));

	//m_player.init(m_world.get(), glm::vec2(-1.0f, -7.0f));
	m_player.init(m_world.get(), glm::vec2(103.0f, -7.0f));

	// init guardians
	m_guardians.clear();

	m_guardians.push_back(new Guardian);
	m_guardians.back()->init(m_world.get(), glm::vec2(16.0f, -6.0f), 0.0f, 5.0f, -1);
	m_guardians.push_back(new Guardian);
	m_guardians.back()->init(m_world.get(), glm::vec2(34.0f, -6.0f), 4.5f, 5.0f, -1);
	m_guardians.back()->setCounter(0.5f);

	m_guardians.push_back(new Guardian);
	m_guardians.back()->init(m_world.get(), glm::vec2(50.0f, -0.5f), 3.5f, 5.0f, -1);

	m_guardians.push_back(new Guardian);
	m_guardians.back()->init(m_world.get(), glm::vec2(68.0f, -3.25f), 4.5f, 5.0f, 1);

	m_guardians.push_back(new Guardian);
	m_guardians.back()->init(m_world.get(), glm::vec2(95.0f, -6.0f), 3.5f, 5.0f, 1);
	m_guardians.push_back(new Guardian);
	m_guardians.back()->init(m_world.get(), glm::vec2(95.0f, 3.0f), 4.5f, 5.0f, -1);
	m_guardians.push_back(new Guardian);
	m_guardians.back()->init(m_world.get(), glm::vec2(95.0f, 13.0f), 3.5f, 5.0f, -1);
	m_guardians.back()->setCounter(0.5f);

	// init crates
	m_crates.clear();
	m_crates.push_back(new Crate);
	m_crates.back()->init(m_world.get(), glm::vec2(13.0f, -7.0f));
	m_crates.push_back(new Crate);
	m_crates.back()->init(m_world.get(), glm::vec2(55.0f, -7.0f));
	m_crates.push_back(new Crate);
	m_crates.back()->init(m_world.get(), glm::vec2(68.0f, -6.75f));
	m_crates.push_back(new Crate);
	m_crates.back()->init(m_world.get(), glm::vec2(86.0f, -7.0f));
	m_crates.push_back(new Crate);
	m_crates.back()->init(m_world.get(), glm::vec2(92.0f, 1.75f));
	m_crates.push_back(new Crate);
	m_crates.back()->init(m_world.get(), glm::vec2(92.0f, 12.f));

	// init bricks
	m_bricks.clear();
	m_walls.clear();

	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(102.0f, 6.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(102.0f, 6.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(102.0f, 7.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(102.0f, 7.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(102.0f, 8.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(102.0f, 8.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(102.0f, 9.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(102.0f, 9.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(102.0f, 10.0f));

	m_walls.push_back(new Wall);
	m_walls.back()->init(m_world.get(), glm::vec2(102.0f, 8.0f), glm::vec2(1.1f, 4.75f));

	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, -4.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, -3.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, -3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, -2.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, -2.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, -1.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, -1.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, -0.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, 0.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, 0.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, 1.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, 1.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, 2.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, 2.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, 3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, 3.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, 4.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, 4.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(103.0f, 5.0f));

	m_walls.push_back(new Wall);
	m_walls.back()->init(m_world.get(), glm::vec2(103.0f, 0.5f), glm::vec2(1.1f, 9.75f));

	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(101.5f, -3.0f));

	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(99.5f, 8.0f));

	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(97.0f, 10.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(96.0f, 10.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(95.0f, 10.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(94.0f, 10.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(93.0f, 10.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(92.0f, 10.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(91.0f, 10.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(90.0f, 10.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(89.0f, 10.5f));

	m_walls.push_back(new Wall);
	m_walls.back()->init(m_world.get(), glm::vec2(93.0f, 10.5f), glm::vec2(9.0f, 0.85f));

	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(84.5f, 8.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(86.25f, 7.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(88.0f, 6.0f));

	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(97.0f, 0.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(96.0f, 0.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(95.0f, 0.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(94.0f, 0.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(93.0f, 0.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(92.0f, 0.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(91.0f, 0.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(90.0f, 0.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(89.0f, 0.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(88.0f, 0.5f));

	m_walls.push_back(new Wall);
	m_walls.back()->init(m_world.get(), glm::vec2(92.5f, 0.5f), glm::vec2(10.0f, 0.85f));

	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(85.0f, 0.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(83.0f, -3.0f));


	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(83.0f, 6.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(83.0f, 6.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(83.0f, 7.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(83.0f, 7.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(83.0f, 8.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(83.0f, 8.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(83.0f, 9.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(83.0f, 9.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(83.0f, 10.0f));

	m_walls.push_back(new Wall);
	m_walls.back()->init(m_world.get(), glm::vec2(83.0f, 8.0f), glm::vec2(1.1f, 4.75f));

	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, -4.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, -3.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, -3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, -2.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, -2.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, -1.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, -1.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, -0.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, 0.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, 0.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, 1.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, 1.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, 2.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, 2.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, 3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, 3.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, 4.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, 4.5f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(82.0f, 5.0f));

	m_walls.push_back(new Wall);
	m_walls.back()->init(m_world.get(), glm::vec2(82.0f, 0.5f), glm::vec2(1.1f, 9.75f));


	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(65.0f, -0.5f));

	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(63.0f, -3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(62.0f, -3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(61.0f, -3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(60.0f, -3.0f));

	m_walls.push_back(new Wall);
	m_walls.back()->init(m_world.get(), glm::vec2(61.5f, -3.0f), glm::vec2(4.0f, 0.85f));

	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(51.0f, -3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(50.0f, -3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(49.0f, -3.0f));

	m_walls.push_back(new Wall);
	m_walls.back()->init(m_world.get(), glm::vec2(50.0f, -3.0f), glm::vec2(3.0f, 0.85f));

	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(42.0f, -3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(41.0f, -3.0f));

	m_walls.push_back(new Wall);
	m_walls.back()->init(m_world.get(), glm::vec2(41.5f, -3.0f), glm::vec2(2.0f, 0.85f));

	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(34.0f, -3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(33.0f, -3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(32.0f, -3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(31.0f, -3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(30.0f, -3.0f));

	m_walls.push_back(new Wall);
	m_walls.back()->init(m_world.get(), glm::vec2(32.0f, -3.0f), glm::vec2(5.0f, 0.85f));

	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(24.0f, -3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(21.0f, -3.0f));

	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(16.0f, -3.0f));
	m_bricks.push_back(new Brick);
	m_bricks.back()->init(m_world.get(), glm::vec2(15.0f, -3.0f));

	m_walls.push_back(new Wall);
	m_walls.back()->init(m_world.get(), glm::vec2(15.5f, -3.0f), glm::vec2(2.0f, 0.85f));

	m_walls.push_back(new Wall);
	m_walls.back()->init(m_world.get(), glm::vec2(58.0f, -9.0f), glm::vec2(144.0f, 2.0f));
	m_walls.push_back(new Wall);
	m_walls.back()->init(m_world.get(), glm::vec2(-3.0f, 0.0f), glm::vec2(1.0f, 12.0f));

	m_finishLine.init(m_world.get(), glm::vec2(110.0f, -0.0f), glm::vec2(1.0f, 12.0f));

	m_background.init();
	//m_houses.init();
}

void GameplayScreen::onExit() {
	m_debugRenderer.dispose();
}

void GameplayScreen::update() {

	// fix camera position
	glm::vec2 cameraPosition;
	glm::vec2 playerPosition;
	glm::vec2 posDiff;

	checkInput();

	switch (m_gameState) {
	case GameState::LOAD :
		loadLevel();
		m_gameState = GameState::PLAY;
		break;
	case GameState::PLAY:
	case GameState::SIGHTED:
	case GameState::END:
		cameraPosition = m_camera.getPosition();
		playerPosition = m_player.getPosition();
		posDiff = cameraPosition - playerPosition;

		if (posDiff.x < 1.0f) {
			m_camera.move(glm::vec2(1.0f - posDiff.x, 0.0f));
		}
		if (posDiff.x > 5.0f) {
			m_camera.move(glm::vec2(5.0f - posDiff.x, 0.0f));
		}
		if (posDiff.y < 0.0f) {
			m_camera.move(glm::vec2(0.0f, 0.0f - posDiff.y));
		}
		if (posDiff.y > 4.0f) {
			m_camera.move(glm::vec2(0.0f, 4.0f - posDiff.y));
		}

		m_camera.update();
		m_hudCamera.update();

		if (m_gameState == GameState::PLAY) {
			m_player.update(m_game->getInputManager());

			for (auto& g : m_guardians) {
				g->update(m_game->getInputManager());
			}
		}

		m_world->Step(1.0f / 60.0f, 6, 2);

		if (m_player.isSighted()) {
			m_gameState = GameState::SIGHTED;
		}

		if (m_player.hasEscaped()) {
			m_gameState = GameState::END;
		}

		if (m_game->getInputManager().isKeyPressed(SDLK_r)) {
			m_gameState = GameState::LOAD;
		}
	default:
		break;
	}

	
}

void GameplayScreen::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_textureProgram.use();

	// Upload texture uniform
	GLint textureUniform = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	// Camera matrix
	glm::mat4 projectionMatrix = m_camera.getCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_spriteBatch.begin(taengine::GlyphSortType::FRONT_TO_BACK);

	m_player.draw(m_spriteBatch);

	if (m_player.hasEscaped()) {

		char buffer[256];

		taengine::Color color;
		if (m_player.getKillCount() < 1) {
			sprintf_s(buffer, "I hope peace can be restored...");
			color.red = 0;
			color.green = 200;
			color.blue = 0;
			color.alpha = 255;
		}
		else if (m_player.getKillCount() < 3) {
			sprintf_s(buffer, "Mom, dad... why is this happening...?");
			color.red = 111;
			color.green = 122;
			color.blue = 35;
			color.alpha = 255;
		}
		else if (m_player.getKillCount() < 5) {
			sprintf_s(buffer, "I.. What I... Did I kill all those people...?");
			color.red = 128;
			color.green = 58;
			color.blue = 20;
			color.alpha = 255;
		}
		else {
			sprintf_s(buffer, "I will kill you all, human scum!!");
			color.red = 186;
			color.green = 0;
			color.blue = 0;
			color.alpha = 255;
		}

		m_spriteFont->draw(m_spriteBatch, buffer, m_player.getPosition() + glm::vec2(0.0f,1.5f), glm::vec2(0.01f),
			2.0f, color, taengine::Justification::MIDDLE);

	}

	for (auto& g : m_guardians) {
		g->draw(m_spriteBatch);
		if (g->hasFoundAnya()) {

			char buffer[256];

			sprintf_s(buffer, g->shout().c_str());

			m_spriteFont->draw(m_spriteBatch, buffer, g->getPosition() + glm::vec2(0.0f, 2.5f), glm::vec2(0.01f),
				2.0f, taengine::Color(128, 128, 255, 255), taengine::Justification::MIDDLE);
		}
	}
	for (auto& c : m_crates) {
		c->draw(m_spriteBatch);
	}
	for (auto& b : m_bricks) {
		b->draw(m_spriteBatch);
	}
	m_background.draw(m_spriteBatch);
	//m_houses.draw(m_spriteBatch);

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_textureProgram.unuse();

	// render light
	m_lightProgram.use();

	pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	// Additive blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	m_spriteBatch.begin();
	for (auto& g : m_guardians) {
		g->drawLight(m_spriteBatch);
	}

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_lightProgram.unuse();

	// reset to regular alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Draw hud

	m_textureProgram.use();

	glActiveTexture(GL_TEXTURE0);

	char buffer[256];

	GLuint textureLocation = m_textureProgram.getUniformLocation("mySampler");
	glUniform1i(textureLocation, 0);

	GLuint pLocation = m_textureProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_hudCamera.getCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));


	m_hudSpriteBatch.begin();

	if (m_gameState == GameState::SIGHTED) {
		sprintf_s(buffer, "You were sighted!");

		m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(m_window->getScreenWidth() / 2.0f, m_window->getScreenHeight() / 2.0f + 64),
			glm::vec2(0.5f), 0.0f, taengine::Color(155, 155, 0, 255), taengine::Justification::MIDDLE);


		sprintf_s(buffer, "Retry? (Press R)");

		m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(m_window->getScreenWidth() / 2.0f, m_window->getScreenHeight() / 2.0f + 32),
			glm::vec2(0.5f), 0.0f, taengine::Color(155, 155, 0, 255), taengine::Justification::MIDDLE);

	}

	if (m_gameState == GameState::END) {
		taengine::Color color;
		if (m_player.getKillCount() < 1) {
			sprintf_s(buffer, "You're free! You shall restore peace once again!");
			color.red = 0;
			color.green = 200;
			color.blue = 0;
			color.alpha = 255;
		}
		else if (m_player.getKillCount() < 3) {
			sprintf_s(buffer, "You escaped, but this trauma will follow you forever");
			color.red = 111;
			color.green = 122;
			color.blue = 35;
			color.alpha = 255;
		}
		else if (m_player.getKillCount() < 5) {
			sprintf_s(buffer, "You're safe, but your mind isn't...");
			color.red = 128;
			color.green = 58;
			color.blue = 20;
			color.alpha = 255;
		}
		else {
			sprintf_s(buffer, "You survived, but you'll only rest when all humans are dead!");
			color.red = 186;
			color.green = 0;
			color.blue = 0;
			color.alpha = 255;

		}

		m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(m_window->getScreenWidth() / 2.0f, m_window->getScreenHeight() / 2.0f + 64),
			glm::vec2(0.5f), 0.0f, color, taengine::Justification::MIDDLE);


		sprintf_s(buffer, "Play again? (Press R)");

		m_spriteFont->draw(m_hudSpriteBatch, buffer, glm::vec2(m_window->getScreenWidth() / 2.0f, m_window->getScreenHeight() / 2.0f + 32),
			glm::vec2(0.5f), 0.0f, color, taengine::Justification::MIDDLE);

	}

	m_hudSpriteBatch.end();
	m_hudSpriteBatch.renderBatch();

	glBindTexture(GL_TEXTURE_2D, 0);
	m_textureProgram.unuse();

	if (m_renderDebug) {
		m_player.drawDebug(m_debugRenderer, taengine::Color(255, 255, 255, 255));

		for (auto& g : m_guardians) {
			g->drawDebug(m_debugRenderer, taengine::Color(255, 255, 255, 255));
		}
		for (auto& c : m_crates) {
			c->drawDebug(m_debugRenderer, taengine::Color(255, 255, 255, 255));
		}
		for (auto& b : m_bricks) {
			b->drawDebug(m_debugRenderer, taengine::Color(255, 255, 255, 255));
		}

		for (auto& w : m_walls) {
			w->drawDebug(m_debugRenderer, taengine::Color(0, 0, 255, 255));
		}

		m_finishLine.drawDebug(m_debugRenderer, taengine::Color(255, 0, 0, 255));

		m_debugRenderer.end();
		m_debugRenderer.render(projectionMatrix, 2.0f);
	}
}

int GameplayScreen::getNextScreenIndex() const {
	return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPreviousScreenIndex() const {
	return SCREEN_INDEX_NO_SCREEN;

}


void GameplayScreen::checkInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		m_game->onSDLEvent(event);
	}
}

