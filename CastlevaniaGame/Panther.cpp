#include "Panther.h"
#include "Sprite.h"
#include "World.h"

Panther::Panther() {}

Panther::Panther(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(24, -24, -14, 14);
	enemyType = PANTHER;

	// ---- update K_1.7
	spriteLeft->_Index = 2;
	spriteRight->_Index = 2;
	// -----------
}

Panther :: ~Panther()
{

}


void Panther::Init(int _X, int _Y)
{
	health = 1;

	isActive = true;
	isSleeping = true;
	hasJumped = false;
	postY = _Y;
	postX = _X;
	if (manager->Simon->isRight)
		velocityX = -30;
	else
		velocityX = 30;
	velocityY = -150;
}

void Panther::Update(const float &_DeltaTime)
{
	sprite = spriteLeft;
	if (manager->Simon->postX > postX - 200)
		isSleeping = false;
	if (!isSleeping)
	{
		if (!hasJumped)
		{
			postX += velocityX * _DeltaTime * 8;
			postY -= velocityY * _DeltaTime;

			timerSprite += _DeltaTime;

			if (timerSprite >= ANIM_TIME)
			{
				velocityY += velocityX*velocityX / 5;
				sprite->Next(4, 4);
				timerSprite = 0;
			}

			if (Enemy::CheckGroundCollision(manager, _DeltaTime))
			{
				hasJumped = true;
			}
		}
		else
		{
			postX += velocityX * _DeltaTime * 8;
			timerSprite += _DeltaTime;

			if (timerSprite >= ANIM_TIME)
			{
				sprite->Next(3, 5);
				timerSprite = 0;
			}
		}			
	}
}



void Panther::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void Panther::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 200;
	isActive = false;
}

void Panther::Collision()
{
	Enemy::Collision();
}

void Panther::CheckActive()
{
	if (postX < Sprite::cameraXLeft || postX > Sprite::cameraXRight)
		isActive = false;
	
}