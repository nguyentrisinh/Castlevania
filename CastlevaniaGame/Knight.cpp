﻿#include "Knight.h"
#include "Sprite.h"
#include "World.h"
int Knight::index = 0;
Knight::Knight() {}

Knight::Knight(LPD3DXSPRITE _SpriteHandler, World *_manager):Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(24, -24, -14, 14);
	this->_manager = _manager;
	enemyType = KNIGHT;
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
	damage = 2;

	startX = _X,
	startY = _Y;
	isActive = true;
	isSleeping = true;
	isFrozen = false;
	timerFrozen = 0.2f;
	position.y = _Y;
	position.x = _X+20;
	velocity.x = -40; //default go from right to left
	sprite = spriteLeft;
	limitRight = startX + 65;
	limitLeft = startX - 100;
	index++;
	
	//A limit special for 3nd knight
	if (index == 3) {
		limitLeft = startX - 70;
		limitRight = startX + 50;
	}

	if (index == 2) {
		limitLeft = startX-20;
		limitRight = startX +20;
	}


}

void Knight::Update(const float &_DeltaTime)
{	
	if (isFrozen)
	{
		timerFrozen -= _DeltaTime;
		if (timerFrozen <= 0) {
			isFrozen = false;
			timerFrozen = 0.2f;
		}
		return;
	}

	//Only update if knight is in camera
	if (isInCamera()) {
		_deltaTime = _DeltaTime;
		
		//Nếu chạm tường bên trái
		if (checkWallCollision() != 0) {
			if (velocity.x > 0)
				sprite = spriteLeft;
			else
				sprite = spriteRight;

			if (velocity.x < 0)
				velocity.x = -velocity.x;
		}
		
		//Set limit right để khỏi rơi xuống
		if (position.x >= limitRight) {
			sprite = spriteLeft;
			if (velocity.x > 0)
				velocity.x = -velocity.x;
		}

		//Set limit right để khỏi rơi xuống
		if (position.x <= limitLeft) {
			sprite = spriteRight;
			if (velocity.x < 0)
				velocity.x = -velocity.x;
		}

		
		//Chắc chắn một lần nữa để con Knight không rơi xuống, đảm bảo luôn trên đất 
		/*
		if (!CheckGroundCollision()) {
			if (velocity.x < 0) {
				sprite = spriteRight;
			}
			else
				sprite = spriteLeft;
			velocity.x = -velocity.x;
		}
		*/
		//Cập nhật theo delta time sau khi xác định được hướng
		position.x += (velocity.x * _deltaTime);
		setSprite();
		
		
	}
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

void Knight::notMovingThroughWall() {
	float collisionScale = 0;
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		GameObject *object = manager->groupQuadtreeCollision->objects[i];

		switch (object->objectType)
		{
		case GROUND_TYPE:
			collisionScale = SweptAABB(object, _deltaTime);
			SlideFromGround(object, _deltaTime, collisionScale);
			break;
		default:
			break;
		}
	}
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
			if (collisionScale < 1.0f)
			{
				return true;
			}
		}
	}
	return false;
}

void Knight::Render()
{
	if (isInCamera())
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

bool Knight::isInCamera() {
	if (position.x >= Sprite::cameraXLeft || position.x <= Sprite::cameraXRight)
		return true;
	return false;
}

void Knight::TakeDamage(int Damage)
{
	Game::gameSound->playSound(HITSOFT);
	health -= Damage;
	if (health <= 0)
	{
		Destroy();
	}
	else
	{
		Effect* effect = Effect::CreateEffect(EFFECT_HIT, position.x + 14, position.y, -1, spriteHandler, manager);
		manager->groupEffect->AddObject(effect);
		position.x -= 4;
	}
}