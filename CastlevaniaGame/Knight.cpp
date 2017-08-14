#include "Knight.h"
#include "Sprite.h"
#include "World.h"

Knight::Knight() {}

Knight::Knight(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(24, -24, -14, 14);
	this->_manager = _manager;
	enemyType = KNIGHT;
	// ---- update K_1.7
	spriteLeft->_Index = 14;
	spriteRight->_Index = 14;
}

Knight :: ~Knight()
{

}


void Knight::Init(int _X, int _Y)
{
	// -----------
	health = 8;

	isActive = true;
	isSleeping = true;
	position.y = _Y;
	position.x = _X;
	if (manager->Simon->isRight)
		velocity.x = -30;
	else
		velocity.x = 30;
	
}

void Knight::Update(const float &_DeltaTime)
{
	velocity.x = -30;
	_deltaTime = _DeltaTime;
	if (checkWallCollision())
		position.x += (-velocity.x * _DeltaTime);
	else
		position.x += velocity.x * _DeltaTime;

	sprite = spriteLeft;
	timerSprite += _DeltaTime;

	if (timerSprite >= ANIM_TIME)
	{
		sprite->Next(14, 17);
		timerSprite = 0;
	}

}

bool Knight::checkWallCollision() {
	float collisionScale = 0;
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		GameObject *object = manager->groupQuadtreeCollision->objects[i];

		switch (object->objectType)
		{
		//Check if collision with zone
		case ZONE_TYPE:
			collisionScale = SweptAABB(object, _deltaTime);
			if (collisionScale >= 1.0f)
				return true;
			return false;
			/*
			if (collisionScale < 1.0f)
			{
				switch (((Ground*)object)->typeGround)
				{
				case GROUND_BRICK3:
					if
						(normaly > 0.1f)//chạm từ trên xuống
						return true;
					break;
				}
			}
			break;
			*/
		default:
			return false;
			break;
		}
	}
	return false;
}
	

bool Knight::CheckGroundCollision()
{
	float collisionScale = 0;
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		GameObject* tempObject = manager->groupQuadtreeCollision->objects[i];
		switch (tempObject->objectType)
		{
		case GROUND_TYPE:
			collisionScale = SweptAABB(tempObject, _deltaTime);
			if (collisionScale < 1.0f)
			{
				switch (((Ground*)tempObject)->typeGround)
				{
				case GROUND_BLOCK:
					if
						(normaly > 0.1f)//chạm từ trên xuống
						return true;
					break;
				}
			}
			break;
		}
	}
	return false;
}

void Knight::Render()
{
	if (isActive)
		sprite->Render(position.x, position.y);
}

void Knight::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 400;
	isActive = false;
}

void Knight::Collision()
{
	Enemy::Collision();
}

void Knight::CheckActive()
{
	if (position.x < Sprite::cameraXLeft || position.x > Sprite::cameraXRight)
		isActive = false;

}