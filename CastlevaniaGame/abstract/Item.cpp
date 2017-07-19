#include "Item.h"

Item::Item() {}

Item::Item(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ITEM_TYPE;
	sizeWidth = 128;
	sizeHeight = 128;

	position.x = 400;
	velocity.x = 0.2f;

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
	position.x += (velocity.x * _DeltaTime);
	if (position.x < 0 || position.x > 500)
	{
		position.x -= (velocity.x * _DeltaTime);
		velocity.x = -velocity.x;
		position.x += (velocity.x * _DeltaTime);
	}
	position.y = 94;

	if (velocity.x > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;
	sprite->Next(0, 1);
}

void Item::Render()
{
	sprite->Render(position.x, position.y);
}

void Item::Destroy()
{

}

void Item::Collision()
{

}