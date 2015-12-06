#define DEBUG_CONSOLE 0

#if DEBUG_CONSOLE != 1
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Game.h"
#include <iostream>

int main()
{
	using namespace SandboxFramework;
	Game* game = new Game("SandboxFramework Window");
	game->Run();
	delete game;
	return 0;
}