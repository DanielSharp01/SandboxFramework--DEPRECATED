#define DEBUG_CONSOLE 1

#if DEBUG_CONSOLE != 1
	#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "MyGame.h"

#include "Audio/AudioDevice.h"
#include "Audio/WaveFile.h"
#include "Audio/AudioSource.h"
#include "Audio/Sound.h"

int main()
{
	using namespace Sand;
	MyGame* game = new MyGame();
	game->Run();
	delete game;

	/*Sand::Audio::AudioDevice* dev = new Sand::Audio::AudioDevice();
	
	Sand::Audio::WaveFile* wav = Sand::Audio::WaveFile::Load("E:/Music/WAV/test.wav");
	Sand::Audio::Sound* sound = new Sand::Audio::Sound(dev, wav);
	Sand::Audio::AudioSource* source = dev->GetAudioSource(0);
	
	source->BindSound(sound);
	source->SetPitch(1.2f); //Nightcore
	source->SetLooping(true);
	source->Play();
	std::cin.get();
	source->Pause();
	std::cout << source->GetPosition() << "s / " << source->GetDuration() << "s" << std::endl;
	std::cin.get();
	source->SetPosition(110);
	source->Play();
	std::cin.get();

	delete sound;
	delete wav;
	delete dev;*/

	return 0;
}