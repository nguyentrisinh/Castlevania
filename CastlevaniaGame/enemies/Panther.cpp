#include "Panther.h"
#include "../engine/Sprite.h"

Panther::Panther() {}

Panther::Panther(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	collider = new Collider();
	collider->setCollider(24, -24, -14, 14);
	isActive = false;

	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_left.bmp", sizeWidth, sizeHeight, 29, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_right.bmp", sizeWidth, sizeHeight, 29, 6);
	sprite = spriteLeft;


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