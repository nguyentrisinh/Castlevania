﻿#include "Heart.h"
#include "World.h"
#include "GroupObject.h"
Heart::Heart() {}

Heart::Heart(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	spriteHandler = _SpriteHandler;
	objectType = ITEM_TYPE;
	itemType = HEART;
	sizeWidth = 64;
	sizeHeight = 64;
	a = 10;
	collider = new Collider();
	collider->setCollider(9, -9, -9, 9);
	velocityX = -20;
	velocityY = -50;
	isActive = false;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", sizeWidth, sizeHeight, 22, 6);
}

Heart :: ~Heart()
{

}

void Heart::Init(int _X, int _Y)
{
	isActive = true;
	timeSurvive = 0;
	postX = _X;
	postY = _Y;
	
	sprite->Next(8, 8);
}


void Heart::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= 3.0f)
		Destroy();
	if (velocityX == 0 && velocityY == 0)
		return;
	a++;
	postX += velocityX * _DeltaTime;
	postY += velocityY * _DeltaTime;

	timerSprite += _DeltaTime;

	if (timerSprite >= 0.2f)
	{
		velocityX = sin(a) * 40;
		sprite->Next(8, 8);
		timerSprite = 0;
	}
	//====Xét collision với ground
	if (Item::CheckGroundCollision(manager, _DeltaTime))
	{
		velocityY = 0;
		velocityX = 0;
	}
	
}

void Heart::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
	
}

void Heart::Destroy()
{
	isActive = false;
	
}

void Heart::Collision(Player *player)
{
	isActive = false;
	player->heart++;
	
}

void Heart::Init(int _X, int _Y, int type)
{
}
