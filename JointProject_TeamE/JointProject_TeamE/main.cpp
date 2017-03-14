#ifdef _DEBUG
 #pragma comment(lib, "sfml-graphics-d.lib")
 #pragma comment(lib, "sfml-audio-d.lib")
 #pragma comment(lib, "sfml-system-d.lib")
 #pragma comment(lib, "sfml-window-d.lib")
 #pragma comment(lib, "sfml-network-d.lib")
 #pragma comment(lib, "libyaml-cppmdd.lib") // YAML
 #pragma comment(lib,"thor-d.lib")			//Thor library
 #pragma comment(lib, "sfeMovie-d.lib")		//SFE Movie library
 #else
 #pragma comment(lib, "sfml-graphics.lib")
 #pragma comment(lib, "sfml-audio.lib")
 #pragma comment(lib, "sfml-system.lib")
 #pragma comment(lib, "sfml-window.lib")
 #pragma comment(lib, "sfml-network.lib")
 #pragma comment(lib, "libyaml-cppmd.lib") // YAML
 #pragma comment(lib,"thor.lib")		   //Thor library
 #pragma comment(lib, "sfeMovie.lib")		//SFE Movie library
 #endif
 #pragma comment(lib, "opengl32.lib")
 #pragma comment(lib, "glu32.lib")

#include "Game.h"
int main()
{
	//std::cout << "All hail the PeterLowe organization" << std::endl;
	Game game;
	game.run();

	return 0;
}