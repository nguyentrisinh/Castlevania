#include <windows.h>
#include <stdlib.h>
#include "engine/MainGame.h"
#define iFullScreen 0
#define FPS 60

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(NULL));

	MainGame CastleVania(hInstance, "Castlevania", iFullScreen, FPS);
	CastleVania.Init();
	CastleVania.Run();

	return 0;
}