#include "Bone.h"
#include "Sprite.h"
#include "World.h"
#include <time.h>
#include "Game.h"

Bone::Bone() {}

Bone::Bone(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(22, -32, -13, 13);
	enemyType = BONE;
	timer = 5;
	sprite->_Index = 27;
	spriteRight->_Index = 27;

}

Bone :: ~Bone()
{

}

void Bone::Init(int _X, int _Y)
{

	health = 24;
	healthBefore = health;
	TimeToAttack = 0;
	isActive = true;
	position.x = _X;
	position.y = _Y;
	if (position.x > manager->Simon->position.x)
	{
		isRight = false;
		sprite = spriteLeft;
	}
	else
	{
		isRight = true;
		sprite = spriteRight;
	}
}


void Bone::Update(const float &_DeltaTime)
{
	sprite->SetColorOverlay(255, 255, 255);
	//random thời gian tấn công
	srand(time(NULL));
	timer = (rand() % 400 + 100) / 100.0;
	if (position.x > manager->Simon->position.x)
	{
		isRight = false;
		sprite = spriteLeft;
	}
	else
	{
		isRight = true;
		sprite = spriteRight;
	}


	//tinh thoi gian tan cong
	TimeToAttack += _DeltaTime;
	if (TimeToAttack >= timer)
	{
		TimeToAttack = 0;
		ActivateBoneFire();
	}

	if (health < healthBefore || isDamage == TRUE) // cho chắc cú
	{
		sprite->SetColorOverlay(255, 0, 0);
	}

	healthBefore = health;
}


void Bone::Render()
{
	if (!isActive)
		return;
	sprite->Render(position.x, position.y);
}

void Bone::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 300;
	isActive = false;
}

void Bone::Collision()
{
	Enemy::Collision();
}

void Bone::CheckActive()
{
	if (position.x < Sprite::cameraXLeft || position.x > Sprite::cameraXRight)
		isActive = false;
}

void Bone::ActivateBoneFire()
{
	EnemyFire *enemyFire = new EnemyFire(manager->spriteHandler, manager);
	enemyFire->Init(position.x, position.y + 14, isRight);
	manager->groupEnemy->AddObject(enemyFire);
}

void Bone::TakeDamage(int damage)
{
	health -= damage;
	if (health <= 0)
	{
		Game::gameSound->playSound(HITSOFT);
		Destroy();
		return;
	}
	Game::gameSound->playSound(HITSTEEL);
}