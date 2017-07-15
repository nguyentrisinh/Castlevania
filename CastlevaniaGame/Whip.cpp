#include "Whip.h"

Whip::Whip(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	collider = new Collider();
	postX = 0;
	postY = 0;
	sizeWidth = 256;
	sizeHeight = 64;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\whip_left.bmp", sizeWidth, sizeHeight, 18, 3);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\whip_right.bmp", sizeWidth, sizeHeight, 18, 3);
	sprite = spriteRight;
	sprite->_Index = 3;

}
Whip::~Whip()
{
	if (spriteLeft != NULL)
	{
		delete spriteLeft;
	}
	if (spriteRight != NULL)
	{
		delete spriteRight;
	}
}
void Whip::Init(int _X, int _Y)
{
	sprite->_Index = 2;
	postX = _X;
	postY = _Y;
}
void Whip::Update(const float &_DeltaTime)
{
	sprite->Next(0, 3);
}
void Whip::Render()
{
	sprite->Render(postX, postY);
}

void Whip::Render(float X, float Y, int simonIndex, bool isRight)
{
	if (isRight)
	{
		sprite = spriteRight;
		collider->setCollider(18, 4, 26, 72);	
	}
	else
	{
		sprite = spriteLeft;
		collider->setCollider(18, 4, -72, -26);
	}
		
	postX = X, postY = Y;
	sprite->_Index = simonIndex - 11;
	Render();
}

void Whip::Update(float X, float Y)
{
	postX = X;
	postY = Y;
}
void Whip::Destroy()
{

}
void Whip::Collision()
{

}