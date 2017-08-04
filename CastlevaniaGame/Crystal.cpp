#include "Crystal.h"
#include "World.h"

Crystal::Crystal() {}

Crystal::Crystal(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ITEM_TYPE;
	itemType = CRYSTAL;
	sizeWidth = 64;
	sizeHeight = 64;

	collider = new Collider();
	velocityY = -100;
	isActive = false;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", sizeWidth, sizeHeight, 22, 6);
}

Crystal :: ~Crystal()
{

}

void Crystal::Init(int _X, int _Y)
{
	isActive = true;
	timeSurvive = 0;
	postX = _X;
	postY = _Y;
	collider->setCollider(10, -10, -16, 16);
	sprite->Next(16, 17);
}


void Crystal::Update(const float &_DeltaTime)
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
			sprite->Next(16, 17);
			timerSprite = 0;
		}
		//Khi chạm nền thì dừng lại
		if (Item::CheckGroundCollision(manager, _DeltaTime))
			velocityY = 0;
	}
}

void Crystal::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Crystal::Destroy()
{
	isActive = false;
}

void Crystal::Collision(Player *player)
{
	isActive = false;
	//xu ly qua man
}

void Crystal::Init(int _X, int _Y, int type)
{
}
