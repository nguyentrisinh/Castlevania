#pragma once
#ifndef _RECTANGLES_H_
#define _RECTANGLES_H_
#include "game.h"
#include "../World.h"

class MainGame :public Game
{
public:
	MainGame() {}
	MainGame(HINSTANCE hInstance, LPCSTR Name, int IsFullScreen, int FrameRate);
	~MainGame();

	LPD3DXSPRITE _SpriteHandler;		//Dung truyen vao spritehandler cua class Sprite
	DWORD last_time;
	LPDIRECT3DSURFACE9 Background;

	Sprite* bg;
	World *world;


	// UI
	int score;
	int timeUI;

	int curHealth;
	int curEnemy;



	Sprite* statusBar;
	Sprite* redEdge;
	Sprite* heart;

protected:
	string convertScoreFormat(int score);
	string convertTimeFormat(int timeUI);
	string convertTwoDigitFormat(int digit);
	void LoadStatusBar(int curHealth, int curEnemy);
	//////////////////////////////////////////
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddevice);
	virtual void UpdateFrame(float _DeltaTime);
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddevice);// , int Delta);
	//////////////////////////////////////
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddevice, float _DeltaTime);
	
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

#endif