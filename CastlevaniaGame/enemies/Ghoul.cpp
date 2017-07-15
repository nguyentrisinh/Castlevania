#include "Ghoul.h"
#include "../engine/Sprite.h"

Ghoul::Ghoul() {}

Ghoul::Ghoul(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	Enemy::Enemy(_SpriteHandler, _manager);
	manager = _manager;
	collider = new Collider();
	collider->setCollider(24, -24, -14, 14);
	isActive = false;

	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_left.bmp", sizeWidth, sizeHeight, 29, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_right.bmp", sizeWidth, sizeHeight, 29, 6);
	sprite = spriteLeft;
	

}

Ghoul :: ~Ghoul()
{

}

void Ghoul::Init(int _X, int _Y, bool isRight)
{
	isActive = true;
	postY = _Y;
	postX = _X;
	if (isRight)
		velocityX = -70;
	else
		velocityX = 70;
}
void Ghoul::Init(int _X, int _Y)
{
	isActive = true;
	postY = _Y;
	postX = _X;
	velocityX = -70;
}

void Ghoul::Update(const float &_DeltaTime)
{
	
	postX += velocityX * _DeltaTime;
	if (velocityX > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;

	timerSprite += _DeltaTime;
	if (timerSprite >= ANIM_TIME)
	{
		sprite->Next(0, 1);
		timerSprite = 0;
	}
			
}



void Ghoul::Render()
{
	sprite->Render(postX, postY);
}

void Ghoul::Destroy()
{

}

void Ghoul::Collision()
{

}

void Ghoul::CheckActive()
{
	if (postX < Sprite::cameraXLeft || postX > Sprite::cameraXRight)
		isActive = false;
}