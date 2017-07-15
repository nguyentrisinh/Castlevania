#include "BlueBat.h"
#include "../engine/Sprite.h"


BlueBat::BlueBat() {}

BlueBat::BlueBat(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	collider = new Collider();
	collider->setCollider(14, -14, -10, 10);
	isActive = false;

	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_left.bmp", sizeWidth, sizeHeight, 29, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_right.bmp", sizeWidth, sizeHeight, 29, 6);
	sprite = spriteLeft;


}

BlueBat :: ~BlueBat()
{

}

void BlueBat::Init(int _X, int _Y, bool isRight)
{
	isActive = true;
	postX = _X;
	postY = _Y;
	velocityY = -250;

	if (isRight)
		velocityX = -160;
	else
		velocityX = 160;
}
void BlueBat::Init(int _X, int _Y)
{
}

void BlueBat::Update(const float &_DeltaTime)
{
	// set sprites with direction
	if (velocityX > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;
	// move

	postX += velocityX * _DeltaTime;
	
	postY += velocityY * _DeltaTime;

	timerSprite += _DeltaTime;
		if (timerSprite >= 0.2f)
	{
		velocityY = velocityY / 2;
		sprite->Next(19, 22);
		timerSprite -= 0.2f;
	}

}



void BlueBat::Render()
{
	sprite->Render(postX, postY);
}

void BlueBat::Destroy()
{

}

void BlueBat::Collision()
{

}

void BlueBat::CheckActive()
{
	if (postX < Sprite::cameraXLeft || postX > Sprite::cameraXRight)
		isActive = false;
}
