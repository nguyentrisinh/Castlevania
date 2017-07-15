#include "Enemy.h"

Enemy::Enemy() 
{
	sizeWidth = 64;
	sizeHeight = 64;
}

Enemy::Enemy(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
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