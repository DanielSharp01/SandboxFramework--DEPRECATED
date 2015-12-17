//TODO: FreeImage as static library
#define DEBUG_CONSOLE 1

#if DEBUG_CONSOLE != 1
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Math/structs.h"
#include "MyGame.h"
#include <iostream>
//#include "IO/ImageReader.h"

int main()
{
	using namespace Sand;
	MyGame* game = new MyGame();
	game->Run();
	delete game;

	/*IO::ImageReader* reader = new IO::ImageReader("C:/Users/Danie/Documents/Visual Studio 2015/Projects/SandboxFramework/SandboxFramework/BoxTexture.png");

	
	BYTE* bytes = reader->GetPixelData();
	unsigned int w = reader->GetWidth();
	unsigned int h = reader->GetHeight();

	for (int i = 0; i < w * h; i++)
	{
		std::cout << +(*bytes++) << " ";
		std::cout << +(*bytes++) << " ";
		std::cout << +(*bytes++) << " ";
		std::cout << +(*bytes++) << " ";
		std::cout << std::endl;
	}

	delete reader;*/

	//std::cin.get();
	return 0;
}