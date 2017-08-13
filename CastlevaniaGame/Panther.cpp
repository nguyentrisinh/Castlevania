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
	// ----------
	this->_manager = _manager;
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
	position.y = _Y;
	position.x = _X;
	if (manager->Simon->isRight)
		velocity.x = -20;
	else
		velocity.x = 20;
	velocity.y = -200;
}

void Panther::Update(const float &_DeltaTime)
{
	sprite = spriteLeft;
	if (manager->Simon->position.x > position.x - 200)
		isSleeping = false;

	if (CheckGroundCollision(_manager, _DeltaTime))
	{
		velocity.y = 0;
	}

	if (!isSleeping)
	{
		if (!hasJumped)
		{
			position.x += velocity.x * _DeltaTime * 8;
			//if (!CheckGroundCollision(_manager, _DeltaTime))
				position.y -= velocity.y * _DeltaTime;

			timerSprite += _DeltaTime;

			if (timerSprite >= ANIM_TIME)
			{
				velocity.y += velocity.x*velocity.x / 5;
				if (CheckGroundCollision(_manager, _DeltaTime))
					sprite->Next(2, 5);
				else
					sprite->Index(4);
				timerSprite = 0;
			}

			if (Enemy::CheckGroundCollision(manager, _DeltaTime))
			{
				hasJumped = true;
			}
		}
		else
		{
			position.x += velocity.x * _DeltaTime * 8;
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
		sprite->Render(position.x, position.y);
}

void Panther::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
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
	if (position.x < Sprite::cameraXLeft || position.x > Sprite::cameraXRight)
		isActive = false;
	
}

bool Panther::CheckGroundCollision(World * manager, const float _DeltaTime) {

	//Check for each object in quad tree is ground and collision?
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		GameObject *object = manager->groupQuadtreeCollision->objects[i];
		
		switch (object->objectType)
		{
		case GROUND_TYPE:
			float collisionScale = SweptAABB(object, _DeltaTime);

			if (collisionScale < 1.0f)
			{
				switch (((Ground*)object)->typeGround)
				{
				case GROUND_BLOCK:
					//position.y = object->position.y + 43;
					return true;
					break;
				default:
					break;
				}
			}
		}
	}
	return false;
}