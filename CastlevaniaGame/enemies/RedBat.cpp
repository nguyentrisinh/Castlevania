#include "RedBat.h"
#include "../engine/Sprite.h"


RedBat::RedBat() {}

RedBat::RedBat(LPD3DXSPRITE _SpriteHandler, World *_manager) : Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -14, -10, 10);

}

RedBat :: ~RedBat()
{

}

void RedBat::Init(int _X, int _Y, bool isRight)
{
	isActive = true;
	postY = _Y;
	postX = _X;
	a = 0;
	if (isRight)
		velocityX = -150;
	else
		velocityX = 150;
}
void RedBat::Init(int _X, int _Y)
{
}

void RedBat::Update(const float &_DeltaTime)
{
	if (velocityX > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;
	postX += velocityX * _DeltaTime;
	a += 0.05;
	timerSprite += _DeltaTime;
	if (timerSprite >= 0.2f)
	{
		postY = 20*sin(a) + 94;
		sprite->Next(7, 10);
		timerSprite = 0;
	}
	
}



void RedBat::Render()
{
	sprite->Render(postX, postY);
}

void RedBat::Destroy()
{

}

void RedBat::Collision()
{

}

void RedBat::CheckActive()
{
	if (postX < Sprite::cameraXLeft || postX > Sprite::cameraXRight)
		isActive = false;
}
