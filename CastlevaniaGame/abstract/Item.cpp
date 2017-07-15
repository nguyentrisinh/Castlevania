#include "Item.h"

Item::Item() {}

Item::Item(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ITEM_TYPE;
	sizeWidth = 128;
	sizeHeight = 128;

	postX = 400;
	velocityX = 0.2f;

	spriteLeft = new Sprite(_SpriteHandler, "bonus.bmp", sizeWidth, sizeHeight, 22, 6);
	sprite = spriteRight;
}

Item :: ~Item()
{

}

void Item::Init(int _X, int _Y)
{

}

void Item::Update(const float &_DeltaTime)
{
	postX += (velocityX * _DeltaTime);
	if (postX < 0 || postX > 500)
	{
		postX -= (velocityX * _DeltaTime);
		velocityX = -velocityX;
		postX += (velocityX * _DeltaTime);
	}
	postY = 94;

	if (velocityX > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;
	sprite->Next(0, 1);
}

void Item::Render()
{
	sprite->Render(postX, postY);
}

void Item::Destroy()
{

}

void Item::Collision()
{

}