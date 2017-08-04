#include "Medusa.h"
#include "Sprite.h"
#include "World.h"


Medusa::Medusa() {}

Medusa::Medusa(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -14, -10, 10);
	enemyType = MEDUSA;
	spriteMedusa = new Sprite(_SpriteHandler, "Resources\\Sprites\\medusa.png", 65, 64, 5, 5);
	thoigiandung = 0;
	isAttack = false;
}

Medusa :: ~Medusa()
{

}

void Medusa::Init(int _X, int _Y)
{
	health = 64;

	isActive = true;
	isAttack = false;
	postX = _X;
	postY = _Y;
	velocityY = -250;
	velocityX = -160;
	a = 0;
	//if (manager->Simon->isRight)
	//	velocityX = -160;
	//else
	//	velocityX = 160;
	
	
}

void Medusa::Update(const float &_DeltaTime)
{
	sprite = spriteMedusa;
	a--;
	if (postY >= 550)
	{
		int r = rand() % 10;
		if (r >= 5)
			isAttack = true;
		else
			isAttack = false;
	}
	if (postX < 400||postX>1000)
	{
		velocityX = 0;
		velocityY = 0;
		thoigiandung += _DeltaTime;
		if (thoigiandung > 2)
		{
			velocityX = -150;
			velocityY = -250;
			if (postX < 400)			
				velocityX *= -1;
			if (postY < 550)
			{
				velocityY *= -1;
				velocityY++;
			}
			thoigiandung = 0;
		}
	}
	postX += velocityX * _DeltaTime;
	postY += velocityY * _DeltaTime;
	
	timerSprite += _DeltaTime;

	if (timerSprite >= 0.2f)
	{
		velocityY = sin(a) * 50;
		sprite->Next(0, 4);
		timerSprite = 0;
	}
	
}



void Medusa::Render()
{
	sprite->Render(postX, postY);
}

void Medusa::Destroy()
{
	// hang 1
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, postX - 32, postY + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, postX + 32, postY + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	// hang 2
	effect = Effect::CreateEffect(EFFECT_SPIRIT, postX - 32, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, postX + 32, postY, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	
	// hang 3
	effect = Effect::CreateEffect(EFFECT_SPIRIT, postX - 32, postY - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, postX + 32, postY - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	manager->Simon->score += 3000;
	isActive = false;

	// tạo item add vào world
	Item* newItem = Item::CreateItem(CRYSTAL, this->postX, this->postY, spriteHandler, manager);
	manager->groupItem->AddObject(newItem);
}

void Medusa::Collision()
{
	Enemy::Collision();
}

void Medusa::CheckActive()
{
	if (manager->Simon->postX <800 - 200 || manager->Simon->postX>800+200) //zone từ 600 - 1000, bắt đầu hành động khi simon còn cách 200
		isActive = false;
	else
		isActive = true;
}
