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

	b2Vec2 gravity(0.0f, -GRAVITY);
	m_world = std::make_unique<b2World>(gravity);

	m_spriteBatch.init();
	m_renderDebug = true;
	m_debugRenderer.init();

	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");

	m_textureProgram.linkShaders();

	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());

	m_camera.setPosition(glm::vec2(0.0f, 0.0f));
	m_camera.setScale(32.0f);

	m_player.init(m_world.get(), glm::vec2(-1.0f, 0.0f));
	m_ground.init(m_world.get(), glm::vec2(28.0f, -9.0f), glm::vec2(84.0f, 2.0f));
	m_background.init();
}

void GameplayScreen::onExit() {
	m_debugRenderer.dispose();
}

void GameplayScreen::update() {

	// fix camera position
	glm::vec2 cameraPosition = m_camera.getPosition();
	glm::vec2 playerPosition = m_player.getPosition();
	glm::vec2 posDiff = cameraPosition - playerPosition;

	if (posDiff.x < 1.0f) {
		m_camera.setPosition(glm::vec2(cameraPosition.x - (posDiff.x - 1.0f), cameraPosition.y));
	}
	if (posDiff.x > 8.0f) {
		m_camera.setPosition(glm::vec2(cameraPosition.x - (posDiff.x - 8.0f), cameraPosition.y));
	}

	m_camera.update();
	checkInput();

	m_player.update(m_game->getInputManager());

	m_world->Step(1.0f / 60.0f, 6, 2);
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
	m_background.draw(m_spriteBatch);

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_textureProgram.unuse();

	if (m_renderDebug) {
		m_player.drawDebug(m_debugRenderer, taengine::Color(255,255,255,255));
		m_ground.drawDebug(m_debugRenderer, taengine::Color(255, 255, 255, 255));
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

