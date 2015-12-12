#define DEBUG_CONSOLE 1

#if DEBUG_CONSOLE != 1
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "MyGame.h"
#include <iostream>

int main()
{
	MyGame* game = new MyGame("SandboxFramework Window");
	game->Run();
	delete game;
	return 0;
}