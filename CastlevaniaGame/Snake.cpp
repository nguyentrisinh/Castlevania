#include "Snake.h"
#include "World.h"
#include "GroupObject.h"

Snake::Snake(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	collider = new Collider();
	collider->setCollider(18, 4, 26, 72);

	postX = 0;
	postY = 0;
	sizeWidth = 32;
	sizeHeight = 20;
	enemyType = SNAKE;
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\snake.png", 32, 20, 2, 2);
	sprite = spriteRight;
	isActive = false;
}
Snake::~Snake()
{
	
}
void Snake::Init(int _X, int _Y)
{
	health = 1;

	isActive = true;
	postX = _X;
	postY = _Y;
	velocityX = -160;
	
}

void Snake::Update(const float &_DeltaTime)
{
	if (!manager->medusa->isAttack)
		isActive = false;
	
	postX += velocityX*_DeltaTime;

	//postY = velocityY*_DeltaTime;
	timerSprite += _DeltaTime;

	if (timerSprite >= 0.2f)
	{
		
		sprite->Next(0, 1);
		timerSprite = 0;
	}
	if (manager->medusa->isAttack )
		CollisionObject(_DeltaTime);
}
void Snake::Render()
{

	if (isActive)
	{
		sprite->Render(postX, postY);
	}

}

void Snake::Destroy()
{
	isActive = false;
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 100;
}
void Snake::Collision()
{}

void Snake::CollisionObject(float _DeltaTime)
{
	float collisionScale = 0;
	GameObject* tempObject;

	/*for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{

		tempObject = manager->groupQuadtreeCollision->objects[i];

		switch (tempObject->objectType)
		{
		case ENEMY_TYPE:
			if (tempObject->objectType == MEDUSA)
				break;
			else
			{
				collisionScale = SweptAABB(tempObject, _DeltaTime);
				if (collisionScale < 1.0f)
				{
					tempObject->Collision();
				}
				break;
			}
			
		default:
			break;
		}
	}*/
}