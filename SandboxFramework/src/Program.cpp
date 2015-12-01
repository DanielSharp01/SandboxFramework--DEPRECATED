#define DEBUG_CONSOLE 1

#if DEBUG_CONSOLE != 1
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Collections/ArrayList.h"
#include "Collections/LinkedList.h"
#include "Collections/Stack.h"
#include "Collections/Queue.h"
#include "Collections/Dictionary.h"

#include "Game.h"

#include <iostream>

#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix.h"

int main()
{
	/*using namespace SandboxFramework;
	Game game("SandboxFramework Window");
	game.Run();*/

	Collections::Dictionary<std::string, int> dict = Collections::Dictionary<std::string, int>();
	dict.Add("ten", 10);
	dict.Add("eleven", 11);
	dict.Add("twelve", 12);
	dict.Add("thirteen", 13);

	for (int i = 0; i < dict.getCount(); i++)
	{
		std::string key = (*dict.getKeys())[i];
		int value = dict[key];

		std::cout << "KV(" << key << ", " << value << ")" << std::endl;
	}

	std::cout << std::endl;
	dict.RemoveAt("twelve");

	for (int i = 0; i < dict.getCount(); i++)
	{
		std::string key = (*dict.getKeys())[i];
		int value = dict[key];

		std::cout << "KV(" << key << ", " << value << ")" << std::endl;
	}

	system("PAUSE");

	return 0;
}