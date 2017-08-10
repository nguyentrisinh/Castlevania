﻿#include "Chicken.h"
#include "World.h"

Chicken::Chicken() {}

Chicken::Chicken(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ITEM_TYPE;
	itemType = CHICKEN;
	sizeWidth = 64;
	sizeHeight = 64;

	collider = new Collider();
	velocityY = -100;
	isActive = false;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", sizeWidth, sizeHeight, 22, 6);
}

Chicken :: ~Chicken()
{

}

void Chicken::Init(int _X, int _Y)
{
	isActive = true;
	timeSurvive = 0;
	postX = _X;
	postY = _Y;
	collider->setCollider(10, -10, -16, 16);
	sprite->Next(10, 10);
}


void Chicken::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= 3.0f)
		isActive = false;
	if (velocityY == 0)
		return;
	if (isActive)
	{
		postY += velocityY * _DeltaTime;

		timerSprite += _DeltaTime;
		if (timerSprite >= 0.2f)
		{
			sprite->Next(10, 10);
			timerSprite = 0;
		}
		//Khi chạm nền thì dừng lại
		if (Item::CheckGroundCollision(manager, _DeltaTime))
			velocityY = 0;
	}
}

void Chicken::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Chicken::Destroy()
{
	isActive = false;
}

void Chicken::Collision(Player *player)
{
	isActive = false;
	player->health += 2;
}

void Chicken::Init(int _X, int _Y, int type)
{
}