#include "Knight.h"
#include "Sprite.h"
#include "World.h"

Knight::Knight() {}

Knight::Knight(LPD3DXSPRITE _SpriteHandler, World *_manager):Enemy(_SpriteHandler, _manager)
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
	health = 100;
	startX = _X,
	startY = _Y;
	isActive = true;
	isSleeping = true;
	position.y = _Y;
	position.x = _X;
	velocity.x = -40; //default go from right to left
	sprite = spriteLeft;
	limitRight = startX + 100;
	/*
	if (manager->Simon->isRight)
		velocity.x = -30;
	else
		velocity.x = 30;
		*/

}

void Knight::Update(const float &_DeltaTime)
{

	_deltaTime = _DeltaTime;

	//Nếu chạm tường bên trái
	if (checkWallCollision() != 0) {
		if (velocity.x > 0)
			sprite = spriteLeft;
		else
			sprite = spriteRight;
		velocity.x = -velocity.x;
	}

	//Set limit right để khỏi rơi xuống
	if (position.x >= limitRight) {
		sprite = spriteLeft;
		velocity.x = -velocity.x;
	}

	//Cập nhật theo delta time sau khi xác định được hướng
	position.x += (velocity.x * _deltaTime);
	setSprite();
}

void Knight::setSprite() {
	timerSprite += _deltaTime;

	if (timerSprite >= ANIM_TIME)
	{
		sprite->Next(14, 17);
		timerSprite = 0;
	}
}
int Knight::checkWallCollision() {
	float collisionScale = 0;
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		GameObject *object = manager->groupQuadtreeCollision->objects[i];

		switch (object->objectType)
		{
		case GROUND_TYPE:
			collisionScale = SweptAABB(object, _deltaTime);
			if (normalx < 0.0f) //đụng tường phải
				return -1;
			if (normalx > 0.0f) //đụng tường trái
				return 1;

			break;
		default:
			break;
		}
	}
	return 0;
}

bool Knight::CheckGroundCollision()
{
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		GameObject *object = manager->groupQuadtreeCollision->objects[i];

		switch (object->objectType)
		{
		case GROUND_TYPE:
			float collisionScale = SweptAABB(object, _deltaTime);
			if (collisionScale != 0.0f)
			{
				return true;
			}
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