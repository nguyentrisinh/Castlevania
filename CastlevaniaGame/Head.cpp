#include "Head.h"
#include "Sprite.h"
#include "World.h"

Head::Head() {}

Head::Head(LPD3DXSPRITE _SpriteHandle, World *_manager) :Enemy(_SpriteHandle, _manager)
{
	collider->setCollider(10, -10, -10, 10);
	enemyType = HEAD;
	spriteLeft->_Index = 23;
	spriteRight->_Index = 23;	
}

Head::~Head() {}

void Head::Init(int _X, int _Y)
{
	health = 1;
	isActive = true;
	position.x = _X;
	position.y = _Y;

	delta = 0;
	if (manager->Simon->isRight)
		velocity.x = -150;
	else
		velocity.x = 150;
	
	lineY = manager->Simon->position.y;
}

void Head::Init(int _X, int _Y, bool isRight)
{
	health = 1;
	isActive = true;

	lineY = manager->Simon->position.y;
	
	position.x = _X;
	delta = 0.6f;

	if (manager->Simon->isRight)
	{
		velocity.x = -150;
		sprite = spriteLeft;
	}
	else
	{
		velocity.x = 150;
		sprite = spriteRight;
	}

}

void Head::Update(const float &_DeltaTime)
{
	position.x += velocity.x * _DeltaTime;
	delta += 0.05;

	position.y = 120 * sin(delta) + lineY;

	timerSprite += _DeltaTime;
	if (timerSprite >= 0.1f)
	{
		sprite->Next(23, 24);
		timerSprite -= 0.1f;	
	}

	if (!IsInCamera())
	{
		this->isActive = false;
	}
}

void Head::Render()
{
	sprite->Render(position.x, position.y);
}

void Head::Destroy()
{
	Effect *effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 200;
	isActive = false;
}

void Head::Collision()
{
	Enemy::Collision();
}

void Head::CheckActive()
{
	if ((position.x < Sprite::cameraX) || (position.x > Sprite::cameraX + 512))
		isActive = false;
}