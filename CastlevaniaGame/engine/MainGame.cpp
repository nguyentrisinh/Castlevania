#include "MainGame.h"
#include <d3d9.h>
#include <d3dx9.h>


#define SIMON_SPEED 0.2f
#define GROUND 94
#define BACKGROUND_FILE "Resources\\map1.bmp"
#define VIEW_PORT_Y 448

MainGame::MainGame(HINSTANCE hInstance, LPCSTR Name, int IsFullScreen, int FrameRate):Game(hInstance, Name, IsFullScreen, FrameRate)
{
	//Just for test
	score = 5896;
	timeUI = 523;

	curHealth = 7;
	curEnemy = 16;

	// create world
}

void MainGame::LoadResources(LPDIRECT3DDEVICE9 _d3ddevice)
{
	srand((unsigned)time(NULL));

	D3DXCreateSprite(_d3ddevice, &_SpriteHandler);
	_d3ddevice->CreateOffscreenPlainSurface(_ScreenWidth, _ScreenHeight, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, &Background, NULL);
	 D3DXLoadSurfaceFromFile(Background, NULL, NULL, BACKGROUND_FILE, NULL, D3DX_DEFAULT, 0, NULL);
	
	// dùng tạm
	bg = new Sprite(_SpriteHandler, BACKGROUND_FILE, 5770, 896, 1, 1);
	world = new World(_SpriteHandler, this);
	world->Init();
	Sprite::cameraY = 448;



	//Hình dùng để render thanh máu, trái tim, khung chứa đồ trên thanh status 
	statusBar = new Sprite(_SpriteHandler, "Resources\\Sprites\\bar_health.bmp", 8, 16, 4, 4);
	redEdge = new Sprite(_SpriteHandler, "Resources\\Sprites\\redEdge.bmp", 80, 59, 1, 1);
	heart = new Sprite(_SpriteHandler, "Resources\\Sprites\\heart.bmp", 16, 13, 1, 1);

}

// --- MAIN UPDATE FUNCTION ---
void MainGame::UpdateFrame(float _DeltaTime)
{
	world->Update(_DeltaTime);
}


// --- UI FUNCTION ---
string MainGame::convertScoreFormat(int score)
{
	if (score < 10)
		return "00000" + std::to_string(score);
	else if (score < 100)
		return "0000" + std::to_string(score);
	else if (score < 1000)
		return "000" + std::to_string(score);
	else if (score < 10000)
		return "00" + std::to_string(score);
	else if (score < 100000)
		return "0" + std::to_string(score);
	else
		return std::to_string(score);
}
string MainGame::convertTimeFormat(int timeUI)
{
	if (timeUI < 10)
		return "000" + std::to_string(timeUI);
	else if (timeUI < 100)
		return "00" + std::to_string(timeUI);
	else if (timeUI < 1000)
		return "0" + std::to_string(timeUI);
	else
		return std::to_string(score);
}
string MainGame::convertTwoDigitFormat(int digit)
{
	if (digit < 10)
		return "0" + std::to_string(digit);
	else
		return std::to_string(digit);
}

void MainGame::LoadStatusBar(int curHealth, int curEnemy)
{
	for (int i = 0; i < curHealth; i++)
	{
		statusBar->Next(0, 0);
		statusBar->Render(70 + i * 8 + heart->cameraX, 410);
	}
	for (int i = curHealth; i < 16; i++)
	{
		statusBar->Next(1, 1);
		statusBar->Render(70 + i * 8 + heart->cameraX, 410);
	}
	for (int i = 0; i < curEnemy; i++)
	{
		statusBar->Next(2, 2);
		statusBar->Render(70 + i * 8 + heart->cameraX, 396);
	}
	for (int i = curEnemy; i < 16; i++)
	{
		statusBar->Next(3, 3);
		statusBar->Render(70 + i * 8 + heart->cameraX, 396);
	}
	redEdge->Render(250 + heart->cameraX, 396);
	heart->Render(300 + heart->cameraX, 410);

}

// --- MAIN RENDER FUNCTION / between BeginScene & EndScene ---
void MainGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv)// , int t)
{
	
	
	d3ddv->ColorFill(backbuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
		
	_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
	
	bg->Render(2850, 448);
	world->Render();
	
	LoadStatusBar(curHealth, curEnemy);
	_SpriteHandler->End();
	//Mấy dòng chữ sẽ hiện lên Status bar
	statusZone1 = "SCORE - " + convertScoreFormat(score) + "                  TIME "
		+ convertTimeFormat(timeUI) +
		"                 STAGE "
		"\n" +
		"\nPLAYER" +
		"\nENEMY";
	statusZone2 = "P - " + convertTwoDigitFormat(world->Simon->heart);
}


void MainGame::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float _DeltaTime)		//Chạy khi nhấn giữ
{
	if (IsKeyDown(DIK_DOWN))
	{
		if (IsKeyDown(DIK_LEFT))
		{
			world->Simon->isRight = false;
		}
		else if (IsKeyDown(DIK_RIGHT))
		{
			world->Simon->isRight = true;
		}
		world->Simon->Move(0, _DeltaTime);
		world->Simon->Down(1);
	}
	else
	{
		world->Simon->Down(0);

		if (IsKeyDown(DIK_LEFT))
		{
			world->Simon->Move(-1, _DeltaTime);
		}
		else if (IsKeyDown(DIK_RIGHT))
		{
			world->Simon->Move(1, _DeltaTime);
		}
		else
		{
			world->Simon->Move(0, _DeltaTime);
		}
	}
}

void MainGame::OnKeyDown(int KeyCode)					//Chỉ nhảy khi vừa nhấn, nhấn giữ không có tác dụng
{
	switch (KeyCode)
	{
	case DIK_SPACE:
		world->Simon->Jump();
		break;
	case DIK_A:
		world->Simon->Injured();
		break;
	case DIK_LCONTROL:
		world->Simon->Attack();
		break;
	}
}

void MainGame::OnKeyUp(int KeyCode) {}

MainGame::~MainGame()
{
	
}