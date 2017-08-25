#include "Crystal.h"
#include "World.h"

Crystal::Crystal() {}

Crystal::Crystal(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ITEM_TYPE;
	itemType = CRYSTAL;
	sizeWidth = 64;
	sizeHeight = 64;

	collider = new Collider();
	velocity.y = -100;
	isActive = false;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", sizeWidth, sizeHeight, 22, 6);
}

Crystal :: ~Crystal()
{

}

void Crystal::Init(int _X, int _Y)
{
	isActive = true;
	timeSurvive = 0;
	position.x = _X;
	position.y = _Y;
	collider->setCollider(10, -10, -16, 16);
	sprite->Next(16, 17);
}


void Crystal::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= 100.0f)
		isActive = false;

	// Effect for crystal
	timerSprite += _DeltaTime;
	if (timerSprite > ANIM_TIME)
	{
		sprite->Next(16, 17);
		timerSprite -= ANIM_TIME;
	}
	if (velocity.y == 0)
		return;
	if (isActive)
	{
		if (CheckGroundCollision(manager, _DeltaTime))
			velocity.y = 0;
		position.y += velocity.y * _DeltaTime;
		
	}
}

void Crystal::Render()
{
	if (isActive)
		sprite->Render(position.x, position.y);
}

void Crystal::Destroy()
{
	isActive = false;
}

void Crystal::Collision(Player *player)
{
	Game::gameSound->playSound(EATCRYSTAL);
	isActive = false;
	//Hoi mau va xu ly qua man
	this->manager->Simon->RestoreHP();
	this->manager->NextLevel();
}

void Crystal::Init(int _X, int _Y, int type)
{
}

bool Crystal::CheckGroundCollision(World * manager, const float _DeltaTime) {
	float collisionScale = 0;
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		GameObject* tempObject = manager->groupQuadtreeCollision->objects[i];
		switch (tempObject->objectType)
		{
		case GROUND_TYPE:
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			if (collisionScale < 1.0f)
			{
				switch (((Ground*)tempObject)->typeGround)
				{
				case GROUND_BLOCK:
						return true;
					break;
				}
			}
			break;
		}
	}
	return false;
}