#include "BlueBat.h"
#include "Sprite.h"
#include "World.h"


BlueBat::BlueBat() {}

BlueBat::BlueBat(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -14, -10, 10);
	enemyType = BLUEBAT;
	isSleeping = true;
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
	damage = 2;

	isActive = true;
	isSleeping = true;

	position.x = _X;
	position.y = _Y;
	velocity.y = -250;

	if (manager->Simon->isRight)
		velocity.x = -160;
	else
		velocity.x = 160;
}

void BlueBat::Update(const float &_DeltaTime)
{
	if (isSleeping)
	{
		// căn k/c giữa Simon và thím dơi
		if (sqrt(
			pow(manager->Simon->position.x - this->position.x, 2) +
			pow(manager->Simon->position.y - this->position.y, 2))
			< 210)
		{
			isSleeping = false;

			// chuyển sprite 
			spriteLeft->_Index = 19;
			spriteRight->_Index = 19;

			if (manager->Simon->isRight)
			{
				velocity.x = -160;
				// set sprites with direction
				sprite = spriteLeft;
			}
			else
			{
				velocity.x = 160;
				// set sprites with direction
				sprite = spriteRight;
			}
		}
	}

	if (isSleeping)
	{
		return;
	}

	// bay (ko ngủ)

	position.x += velocity.x * _DeltaTime;

	position.y += velocity.y * _DeltaTime;

	timerSprite += _DeltaTime;
	if (timerSprite >= 0.2f)
	{
		velocity.y = velocity.y / 2;
		sprite->Next(19, 22);
		timerSprite -= 0.2f;
	}

}



void BlueBat::Render()
{
	sprite->Render(position.x, position.y);
}

void BlueBat::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
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
	if (position.x < Sprite::cameraXLeft || position.x > Sprite::cameraXRight)
		isActive = false;
}
