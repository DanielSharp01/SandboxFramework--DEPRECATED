#pragma once

#include "Game.h"

class MyGame : public SandboxFramework::Game
{
public:
	MyGame(std::string title);
protected:
	void Initialize() override;
	void LoadContent() override;
	void Update() override;
	void Draw() override;
	void UnloadContent() override;
};