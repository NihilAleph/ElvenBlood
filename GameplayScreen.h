#pragma once
#include <taengine\IGameScreen.h>
#include <taengine\Camera2D.h>
#include <taengine\GLSLProgram.h>
#include <taengine\Window.h>
#include <taengine\DebugRenderer.h>
#include <taengine\SpriteFont.h>
#include <taengine\AudioEngine.h>
#include <Box2D\Box2D.h>
#include "Player.h"
#include "Guardian.h"
#include "Wall.h"
#include "Crate.h"
#include "Brick.h"
#include "Sensor.h"
#include "Background.h"
#include "Houses.h"
#include "ContactListener.h"

enum class GameState {
	LOAD, BEGIN, PLAY, SIGHTED, END
};

class GameplayScreen : public taengine::IGameScreen
{
public:
	GameplayScreen(taengine::Window* window);
	~GameplayScreen();

	virtual void build() override;
	virtual void destroy() override;

	virtual void onEntry() override;
	virtual void onExit() override;

	virtual void update() override;
	virtual void draw() override;

	virtual int getNextScreenIndex() const override;
	virtual int getPreviousScreenIndex() const override;

	void loadLevel();

private:
	taengine::Camera2D m_camera;
	taengine::GLSLProgram m_textureProgram;
	taengine::GLSLProgram m_lightProgram;
	taengine::Window* m_window;

	taengine::Camera2D m_hudCamera;
	taengine::SpriteBatch m_hudSpriteBatch;

	bool m_renderDebug;
	taengine::DebugRenderer m_debugRenderer;

	taengine::SpriteBatch m_spriteBatch;
	taengine::SpriteFont* m_spriteFont;

	taengine::AudioEngine m_audioEngine;

	std::unique_ptr<b2World> m_world = nullptr;

	Player m_player;
	std::vector<Guardian*> m_guardians;
	std::vector<Crate*> m_crates;
	std::vector<Brick*> m_bricks;
	std::vector<Wall*> m_walls;
	Sensor m_finishLine;

	Background m_background;
	Houses m_houses;
	ContactListener m_contactListener;

	GameState m_gameState;

	void checkInput();

	float m_timer;

};

