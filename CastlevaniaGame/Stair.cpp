#include "Stair.h"

Stair::Stair(LPD3DXSPRITE _SpriteHandler, World *_manager, int _Type)
{
	manager = _manager;
	objectType = STAIR_TYPE;
	isBreakable = false;
	collider = new Collider();
	collider->setCollider(26, -32, -32, 32);
	stairType = _Type;
}

Stair::Stair(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = STAIR_TYPE;
	isBreakable = false;
	collider = new Collider();
	collider->setCollider(26, -32, -32, 32);

}

Stair :: ~Stair()
{

}

void Stair::Init(int _X, int _Y)
{
	position.x = _X;
	position.y = _Y;
	isActive = true;
}

void Stair::Update(const int &_deltaTime)
{
}

void Stair::Render()
{
	return;
}

void Stair::Destroy()
{

}

void Stair::Collision()
{

}

Stair* Stair::CreateStair(int* parameters, LPD3DXSPRITE spriteHandler, World *manager)
{
	Stair* newStair = NULL;

	newStair = new Stair(spriteHandler, manager, parameters[1] % 100);
	newStair->Init(parameters[2], parameters[3]);

	return newStair;
}