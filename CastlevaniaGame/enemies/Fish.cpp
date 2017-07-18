#include "Fish.h"
#include "../engine/Sprite.h"
#include <time.h>

Fish::Fish() {}

Fish::Fish(LPD3DXSPRITE _SpriteHandler, World *_manager): Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(22, -32, -13, 13);
	isFiring = false;
	timer = 5;
	sprite->_Index = 12;
	spriteRight->_Index = 12;
}

Fish :: ~Fish()
{

}

void Fish::Init(int _X, int _Y, bool isRight)
{
	isFiring = 0;
	isActive = true;
	postY += 10;
	velocityY = 450;
	postX = _X;
	if (isRight)
		velocityX = -80;
	else
		velocityX = 80;
	jumping = true;
	
}
void Fish::Init(int _X, int _Y)
{
}

void Fish::Update(const float &_DeltaTime)
{
	srand(time(NULL));
	timer = (rand() % 300 + 50) / 100.0;
	if (velocityX > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;

	velocityY += -(600 *_DeltaTime);
	postY += (velocityY * _DeltaTime);

	if (velocityY < 0 && postY < 94)
	{
		
		jumping = false;
		postY = 94;
		postX += velocityX * _DeltaTime;
		isFiring += _DeltaTime;
		timerSprite += _DeltaTime;
		if (timerSprite >= 2*ANIM_TIME)
		{
	
			if (isFiring >= timer)
			{
				sprite->_Index = 11;
				isFiring = 0;
				velocityX = -velocityX;
			}
			else
			{
				sprite->Next(12, 13);
			}
			timerSprite = 0;
		}
	}
}

void Fish::Update(float _X, float _Y)
{

}


void Fish::Render()
{
	sprite->Render(postX, postY);
}

void Fish::Destroy()
{

}

void Fish::Collision()
{

}

void Fish::CheckActive()
{
	if (postX < Sprite::cameraXLeft || postX > Sprite::cameraXRight)
		isActive = false;
}