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
	m_renderDebug = false;
	m_debugRenderer.init();

	m_textureProgram.compileShaders("Shaders/textureShading.vert", "Shaders/textureShading.frag");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");

	m_textureProgram.linkShaders();

	m_camera.init(m_window->getScreenWidth(), m_window->getScreenHeight());

	m_camera.setPosition(glm::vec2(0.0f, 0.0f));
	m_camera.setScale(32.0f);

	m_player.init(m_world.get(), glm::vec2(0.0f, 0.0f));
	m_wall.init(m_world.get(), glm::vec2(0.0f, -9.0f), glm::vec2(20.0f, 2.0f));
}

void GameplayScreen::onExit() {
	m_debugRenderer.dispose();
}

void GameplayScreen::update() {
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

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();
	m_textureProgram.unuse();

	if (m_renderDebug) {
		m_player.drawDebug(m_debugRenderer, taengine::Color(255,255,255,255));
		m_wall.drawDebug(m_debugRenderer, taengine::Color(255, 255, 255, 255));
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

