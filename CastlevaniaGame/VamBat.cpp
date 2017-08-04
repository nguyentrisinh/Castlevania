#include "VamBat.h"
#include "Sprite.h"
#include "World.h"


VamBat::VamBat() {}

VamBat::VamBat(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -14, -10, 10);
	enemyType = VAMBAT;
	spriteVamBat = new Sprite(_SpriteHandler, "Resources\\Sprites\\VamBat.png", 96, 46, 3, 3);
}

VamBat :: ~VamBat()
{

}

void VamBat::Init(int _X, int _Y)
{
	isActive = true;
	postX = _X;
	postY = _Y;
	velocityY = -250;
	velocityX = -160;
	//if (manager->Simon->isRight)
	//	velocityX = -160;
	//else
	//	velocityX = 160;
}

void VamBat::Update(const float &_DeltaTime)
{
	// set sprites with direction
	/*if (velocityX > 0)
		sprite = spriteRight;
	else
		sprite = spriteLeft;*/
	// move
	sprite = spriteVamBat;
	if (postX >= 1000 - 400)
	{
		postX += velocityX * _DeltaTime;
		postY += velocityY * _DeltaTime;
	}
	
	timerSprite += _DeltaTime;
	if (timerSprite >= 0.2f)
	{
		velocityY = velocityY / 2;
		sprite->Next(0, 2);
		timerSprite -= 0.2f;
	}
	else
	{
		velocityY = -250;
	}

}



void VamBat::Render()
{
	sprite->Render(postX, postY);
}

void VamBat::Destroy()
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

void VamBat::Collision()
{
	Enemy::Collision();
}

void VamBat::CheckActive()
{
	if (manager->Simon->postX<1000-200 || manager->Simon->postX>1500) //zone của vamBat từ 1000 - 15000, bắt đầu hành động khi simon còn cách 200
		isActive = false;  
	else
		isActive = true;
}
