#define DEBUG_CONSOLE 1

#if DEBUG_CONSOLE != 1
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "MyGame.h"

int main()
{
	using namespace Sand;
	MyGame* game = new MyGame();
	game->Run();
	delete game;
	
	std::cin.get();
	return 0;
}