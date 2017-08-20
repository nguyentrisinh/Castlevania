#include "Ghost.h"
#include "World.h"

Ghost::Ghost() {}

Ghost::Ghost(LPD3DXSPRITE _SpriteHandler, World *_manager) : Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -14, -10, 10);
	enemyType = GHOST;
	manager = _manager;

	spriteLeft->_Index = 25;
	spriteRight->_Index = 25;
}

Ghost::~Ghost() {}

void Ghost::Init(int _X, int _Y)
{
	health = 3;
	damage = 1;

	isActive = true;
	position.x = _X;
	position.y = _Y;

	if (manager->Simon->isRight)
		velocity.x = -70;
	else
		velocity.x = 70;
}

void Ghost::Init(int _X, int _Y, bool isRight)
{
	health = 3;
	damage = 1;

	isActive = true;
	position.x = _X;
	position.y = _Y;

	if (isRight)
		velocity.x = -70;
	else
		velocity.x = 70;
	
}

void Ghost::Update(const float &_DeltaTime)
{
	if (velocity.x < 0)
		sprite = spriteLeft;
	else
		sprite = spriteRight;

	if (manager->Simon->position.y > position.y)
		velocity.y = 10;
	else
		velocity.y = -10;
	
	timerSprite += _DeltaTime;
	if (timerSprite >= ANIM_TIME)
	{
		sprite->Next(25, 26);
		velocity.y = velocity.y / 2;
		timerSprite -= ANIM_TIME;
	}

	position.x += velocity.x * _DeltaTime;
	position.y += velocity.y * _DeltaTime;

	if (!IsInCamera())
		this->isActive = false;
}

void Ghost::Render()
{
	sprite->Render(position.x, position.y);
}

void Ghost::Collision()
{
	Enemy::Collision();
}

void Ghost::Destroy()
{
	Effect *effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	manager->Simon->score += 200;
	isActive = false;
}

void Ghost::CheckActive()
{
	if (position.x > Sprite::cameraX + 512)
		isActive = false;
	else
		isActive = true;
}