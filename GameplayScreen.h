#pragma once
#include <taengine\IGameScreen.h>
#include <taengine\Camera2D.h>
#include <taengine\GLSLProgram.h>
#include <taengine\Window.h>
#include <taengine\DebugRenderer.h>
#include <Box2D\Box2D.h>
#include "Player.h"
#include "Wall.h"

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

	const float GRAVITY = 9.81f;

private:
	taengine::Camera2D m_camera;
	taengine::GLSLProgram m_textureProgram;
	taengine::Window* m_window;

	bool m_renderDebug;
	taengine::DebugRenderer m_debugRenderer;

	taengine::SpriteBatch m_spriteBatch;

	std::unique_ptr<b2World> m_world = nullptr;

	Player m_player;
	Wall m_wall;

	void checkInput();

};

