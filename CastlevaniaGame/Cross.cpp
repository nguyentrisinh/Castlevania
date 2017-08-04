#include "Cross.h"
#include "World.h"

Cross::Cross() {}

Cross::Cross(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ITEM_TYPE;
	itemType = CROSS;
	sizeWidth = 64;
	sizeHeight = 64;

	collider = new Collider();
	velocityY = -80;
	isActive = false;
	
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", sizeWidth, sizeHeight, 22, 6);
	
}

Cross :: ~Cross()
{

}

void Cross::Init(int _X, int _Y)
{
	isActive = true;
	
	timeSurvive = 0;
	postX = _X;
	postY = _Y;
	collider->setCollider(14, -14, -14, 14);
	sprite->Next(5, 5);
}


void Cross::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= 6.0f)
		isActive = false;
	if (velocityY == 0)
		return;
	if (isActive)
	{
		postY += velocityY * _DeltaTime;

		timerSprite += _DeltaTime;
		if (timerSprite >= 0.2f)
		{
			sprite->Next(5, 5);
			timerSprite = 0;
		}
		//Khi chạm nền thì dừng lại
		if (Item::CheckGroundCollision(manager, _DeltaTime))
			velocityY = 0;
	}

}

void Cross::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Cross::Destroy()
{
	isActive = false;
}

void Cross::Collision(Player *player)
{
	isActive = false;
	manager->isFlash = true;
	
	//tieu diet tat ca enemy trong viewport, tru boss
	for (int i = 0; i < manager->groupEnemy->number; i++)
	{
		GameObject* temp = manager->groupEnemy->objects[i];
		if (temp->postX >= Sprite::cameraX && temp->postX <= Sprite::cameraX + 512 &&
			temp->postY >= Sprite::cameraY - 448 && temp->postY <= Sprite::cameraY &&
			temp->objectType != MEDUSA && temp->objectType != VAMBAT)
			temp->isActive = false;
	}
}