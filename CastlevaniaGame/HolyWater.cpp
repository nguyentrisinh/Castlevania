#include "HolyWater.h"
#include "World.h"
#include "GroupObject.h"


HolyWater::HolyWater(LPD3DXSPRITE _SpriteHandler, World *_manager) :Projectile(_SpriteHandler, _manager)
{
	projectileType = HOLYWATER;
	sizeWidth = 64;
	sizeHeight = 64;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_left.bmp", sizeWidth, sizeHeight, 9, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\subweapon_right.bmp", sizeWidth, sizeHeight, 9, 6);
	sprite = spriteRight;
	sprite->_Index = 8;
	spriteRight->_Index = 8;
	spriteLeft->_Index = 8;
	Damage = 2;
	isReverted = false;

}
HolyWater::~HolyWater()
{
	if (spriteLeft != NULL)
	{
		delete spriteLeft;
	}
	if (spriteRight != NULL)
	{
		delete spriteRight;
	}
}
void HolyWater::Init(int _X, int _Y)
{
	isActive = true;
	position.x = _X;
	position.y = _Y;
	isRight = manager->Simon->isRight;

	velocity.y = 400;

	if (isRight)
	{
		velocity.x = 150;
		sprite = spriteRight;
	}
	else
	{
		velocity.x = -150;
		sprite = spriteLeft;
	}
	
}

void HolyWater::Render()
{
	if (this->isActive)
		this->sprite->Render(position.x, position.y);
}

void HolyWater::Update(const float &_DeltaTime)
{
	if (!this->isActive)
		return;

	this->timerSprite += _DeltaTime;


	this->position.x += this->velocity.x * _DeltaTime;
	this->position.y += this->velocity.y * _DeltaTime;
	
	this->velocity.y -= 1000 * _DeltaTime;

	this->CollisionObject(_DeltaTime);

}

void HolyWater::CollisionObject(float _DeltaTime)
{
	GameObject *tempObject;

	for (int i = 0; i < this->manager->groupQuadtreeCollision->number; i++)
	{
		tempObject = this->manager->groupQuadtreeCollision->objects[i];

		// Loại bỏ các trường hợp nếu va chạm phải các object không phải là GROUND
		switch (tempObject->objectType)
		{
		case GROUND_TYPE:
			float collisionScale = this->SweptAABB(tempObject, _DeltaTime);

			if (collisionScale != 1.0f)
			{
				this->Collision();
				this->Destroy();
			}

			break;
		}
	}
}

void HolyWater::Destroy()
{
	this->isActive = false;
}

void HolyWater::Collision()
{
	int count = 0; // Biến dùng để dêm số HolyFire đang cháy 

	for (int i = 0; i < 3; i++)
	{
		if (this->manager->holyWater[i]->isActive)
			count++;
	}

	if (count <= this->manager->Simon->weaponNumber)
	{
		this->manager->holyFire[count]->Init(this->position.x, this->position.y);
		Game::gameSound->playSound(HOLYWATERBREAK);
	}
}

