#include "Projectile.h"

// === CONSTRUCTOR === DESTRUCTOR ===
Projectile::Projectile() {}

Projectile::Projectile(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = PROJECTILE_TYPE;
}


Projectile::~Projectile()
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

// ===== VIRTUAL =====
void Projectile::Init(int _X, int _Y)
{
	isActive = true;

	postX = _X;
	postY = _Y;
}

// ---=== THE MAIN PROCESSING ===---
void Projectile::Update(const float &_DeltaTime)
{
	postX += (velocityX * _DeltaTime);
	postY += (velocityY * _DeltaTime);
	//postY = 94;

	if (velocityX != 0)
		sprite->Next(0, 3);
}

void Projectile::Render()
{
	sprite->Render(postX, postY);
}

void Projectile::Destroy() {}

void Projectile::Collision() {}

