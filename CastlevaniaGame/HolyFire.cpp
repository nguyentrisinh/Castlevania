#include "HolyFire.h"
#include "World.h"
#include "GroupObject.h"

HolyFire::HolyFire(LPD3DXSPRITE _SpriteHandler, World *_manager) :Projectile(_SpriteHandler, _manager)
{
	projectileType = HOLYFIRE;
	sizeWidth = 64;
	sizeHeight = 64;
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\effect.bmp", sizeWidth, sizeHeight, 9, 6);
	sprite = spriteRight;
	sprite->_Index = 0;
	this->collider->setCollider(5, -5, -10, 10);

	Damage = 2;
}
HolyFire::~HolyFire()
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
void HolyFire::Init(int _X, int _Y)
{
	timeActive = 0;
	isActive = true;
	this->timerDamage = 0;
	position.x = _X;
	position.y = _Y;

}

void HolyFire::Update(const float &_DeltaTime)
{
	if (timeActive >= LIFE_TIME)
	{
		isActive = false;
		return;
	}
	timerSprite += _DeltaTime;
	timeActive += _DeltaTime;
	if (timerSprite >= ANIM_TIME)
	{
		sprite->Next(0, 4);
		timerSprite -= ANIM_TIME;
	}
	if (!IsInCamera())
		isActive = false;

	this->CollisionObject(_DeltaTime);
}
void HolyFire::Render()
{
	if (isActive)
	{
		sprite->Render(position.x, position.y);
	}

}

void HolyFire::Destroy()
{
	isActive = false;
}
void HolyFire::Collision()
{
	
}

