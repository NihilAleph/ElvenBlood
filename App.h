#pragma once
#include <taengine\IMainGame.h>
#include <memory>
#include "GameplayScreen.h"

class App : public taengine::IMainGame
{
public:
	App();
	~App();

	virtual void onInit() override;
	virtual void onExit() override;
	virtual void addScreens() override;

private:
	std::unique_ptr<GameplayScreen> m_gameplayScreen = nullptr;
};

