﻿#include "Multiply.h"
#include "World.h"

Multiply::Multiply() {}

Multiply::Multiply(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ITEM_TYPE;
	itemType = MULTIPLY;
	sizeWidth = 64;
	sizeHeight = 64;

	collider = new Collider();
	velocityY = -80;
	isActive = false;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", sizeWidth, sizeHeight, 22, 6);
}

Multiply :: ~Multiply()
{

}

void Multiply::Init(int _X, int _Y)
{
	isActive = true;
	timeSurvive = 0;
	postX = _X;
	postY = _Y;
	collider->setCollider(14, -14, -14, 14);
	if (manager->Simon->weaponNumber < 2)
		sprite->Next(11, 11);
	else
		sprite->Next(12, 12);
}


void Multiply::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= 5.0f)
		isActive = false;
	if (velocityY == 0)
		return;
	if (isActive)
	{
		postY += velocityY * _DeltaTime;

		timerSprite += _DeltaTime;
		if (timerSprite >= 0.2f)
		{
			if (manager->Simon->weaponNumber < 2)
				sprite->Next(11, 11);
			else
				sprite->Next(12, 12);
			timerSprite = 0;
		}
		//Khi chạm nền thì dừng lại
		if (Item::CheckGroundCollision(manager, _DeltaTime))
			velocityY = 0;
	}


}

void Multiply::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Multiply::Destroy()
{
	isActive = false;
}

void Multiply::Collision(Player *player)
{
	isActive = false;
	if (player->weaponNumber < 3)
		player->weaponNumber++;
}