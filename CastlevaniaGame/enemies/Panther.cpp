#include "Panther.h"
#include "../engine/Sprite.h"

Panther::Panther() {}

Panther::Panther(LPD3DXSPRITE _SpriteHandler, World *_manager) : Enemy(_SpriteHandler, _manager)
{

	collider->setCollider(6, -32, -14, 14);


}

Panther :: ~Panther()
{

}

void Panther::Init(int _X, int _Y, bool isRight)
{
	isActive = true;
	postY = _Y;
	postX = _X;
	if (isRight)
		velocityX = -150;
	else
		velocityX = 150;
}
void Panther::Init(int _X, int _Y)
{
}

void Panther::Update(const float &_DeltaTime)
{

	postX += velocityX * _DeltaTime;
	if (velocityX > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;

	timerSprite += _DeltaTime;
	if (timerSprite >= ANIM_TIME)
	{
		sprite->Next(3, 4);
		timerSprite = 0;
	}

}



void Panther::Render()
{
	sprite->Render(postX, postY);
}

void Panther::Destroy()
{

}

void Panther::Collision()
{

}

void Panther::CheckActive()
{
	if (postX < Sprite::cameraXLeft || postX > Sprite::cameraXRight)
		isActive = false;
}