#include "BlueBat.h"
#include "Sprite.h"
#include "World.h"


BlueBat::BlueBat() {}

BlueBat::BlueBat(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -14, -10, 10);
	enemyType = BLUEBAT;
	// ---- update K_1.7
	spriteLeft->_Index = 18;
	spriteRight->_Index = 18;
}

BlueBat :: ~BlueBat()
{

}

void BlueBat::Init(int _X, int _Y)
{
	// -----------
	health = 1;

	isActive = true;
	postX = _X;
	postY = _Y;
	velocityY = -250;

	if (manager->Simon->isRight)
		velocityX = -160;
	else
		velocityX = 160;
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
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 200;
	isActive = false;
}

void BlueBat::Collision()
{
	Enemy::Collision();
}

void BlueBat::CheckActive()
{
	if (postX < Sprite::cameraXLeft || postX > Sprite::cameraXRight)
		isActive = false;
}
