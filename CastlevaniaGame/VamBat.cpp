#include "VamBat.h"
#include "Sprite.h"
#include "World.h"


VamBat::VamBat() {}

VamBat::VamBat(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	health = 16;
	collider->setCollider(14, -14, -10, 10);
	enemyType = VAMBAT;
	spriteVamBat = new Sprite(_SpriteHandler, "Resources\\Sprites\\VamBat.png", 96, 46, 3, 3);
}

VamBat :: ~VamBat()
{

}

void VamBat::Init(int _X, int _Y)
{
	sprite = spriteVamBat;
	isActive = true;
	isSleep = true;
	position.x = _X;
	position.y = _Y;
	velocity.y = -200;
	velocity.x = -160;
	timerPause = 2;
	//if (manager->Simon->isRight)
	//	velocity.x = -160;
	//else
	//	velocity.x = 160;
}

void VamBat::Update(const float &_DeltaTime)
{
	// set sprites with direction
	/*if (velocity.x > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;*/
	// move

	if (isSleep)
	{
		sprite->Next(0, 0);
		timerPause -= _DeltaTime;
		if (timerPause < 0)
		{
			if (position.x > manager->Simon->position.x + 30 || position.x < manager->Simon->position.x - 30)
			{
				isSleep = false;
				timerPause = 2;
			}
		}
	}
	else
	{	
		if (position.y > 685)
		{
			velocity.x = 0;
			velocity.y = -30;
		}
		else
		{
			if (position.y < 550)
			{
				velocity.y = 150;
			}

			if (position.y > 650)
			{
				velocity.y = -150;
			}

			if (position.x < 5250 || position.x > 5656)
			{
				velocity.x = 0;
				velocity.y = 0;
				timerPause -= _DeltaTime;
				if (timerPause < 0)
				{
					if (position.x < 5406)
						velocity.x = 150;
					else
						velocity.x = -150;
					timerPause = 1;
				}
			}
			else
			{
				if (velocity.x == 0)
					velocity.x = -160;
			}
		}

		timerSprite += _DeltaTime;
		if (timerSprite >= 0.2f)
		{
			velocity.y -= velocity.x / 5;
			sprite->Next(1, 2);
			timerSprite -= 0.2f;
		}

		position.x += velocity.x * _DeltaTime;
		position.y += velocity.y * _DeltaTime;
	}	
}



void VamBat::Render()
{
	sprite->Render(position.x, position.y);
}

void VamBat::Destroy()
{
	//hang 1 
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x - 32, position.y + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x + 32, position.y + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	//hang 2 
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x - 32, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x + 32, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	//hang 3 
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x - 32, position.y - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y -32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x + 32, position.y - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	manager->Simon->score += 3000;
	isActive = false;

	// tạo item add vào world
	Item* newItem = Item::CreateItem(CRYSTAL, this->position.x, this->position.y, spriteHandler, manager);
	manager->groupItem->AddObject(newItem);
	health = 0;
}

void VamBat::Collision()
{
	Enemy::Collision();
}

void VamBat::CheckActive()
{
	if (manager->Simon->position.x < position.x - 200) //zone của vamBat từ 10	00 - 1500, bắt đầu hành động khi simon còn cách 200
		isActive = false;  
	else
		isActive = true;
}

void VamBat::TakeDamage(int Damage)
{
	Effect* effect = Effect::CreateEffect(EFFECT_HIT, position.x + 14, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	health -= Damage;

	if (health <= 0)
		Destroy();
}
