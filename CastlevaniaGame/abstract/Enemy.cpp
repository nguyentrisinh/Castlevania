#include "Enemy.h"

Enemy::Enemy() 
{
	sizeWidth = 64;
	sizeHeight = 64;
}

Enemy::Enemy(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	collider = new Collider();
	sizeWidth = 64;
	sizeHeight = 64;
	isActive = false;
	spriteHandler = _SpriteHandler;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_left.bmp", sizeWidth, sizeHeight, 29, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_right.bmp", sizeWidth, sizeHeight, 29, 6);
	sprite = spriteLeft;
}

Enemy :: ~Enemy()
{

}

void Enemy::Init(int _X, int _Y)
{
}

void Enemy::Init(int _X, int _Y, bool isRight)
{
}


void Enemy::Update(const float &_DeltaTime)
{
}


void Enemy::Render()
{
}

void Enemy::Destroy()
{

}

void Enemy::Collision()
{

}



void Enemy::CheckActive()
{
}