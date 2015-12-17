#pragma once

#include "Game.h"

class MyGame : public Sand::Game
{
public:
	MyGame(std::string title = "Test");
protected:
	std::string initialTitle;

	void Initialize() override;
	void LoadContent() override;
	void Update() override;
	void Draw() override;
	void UnloadContent() override;
};