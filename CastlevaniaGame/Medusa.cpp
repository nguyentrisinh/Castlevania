#include "Medusa.h"
#include "Sprite.h"
#include "World.h"


Medusa::Medusa() {}

Medusa::Medusa(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -14, -10, 10);
	enemyType = MEDUSA;
	spriteMedusa = new Sprite(_SpriteHandler, "Resources\\Sprites\\medusa.png", 65, 64, 5, 5);
	sprite = spriteMedusa;
	timePause = 0;
	isAttack = false;
	velocity.y = 20;
	velocity.x = 20;
	
}

Medusa :: ~Medusa()
{

}

void Medusa::Init(int _X, int _Y)
{
	health = 64;
	isActive = true;
	isAttack = false;
	position.x = _X;
	position.y = _Y;
	limitTop = _Y;
	limitBot = _Y - 100;
	
}

void Medusa::Update(const float &_DeltaTime)
{
	_deltaTime = _DeltaTime;
	
	switch (way) {
	case 0:
		moveRightDown(way);
		break;
	case 1:
		moveRightUp(way);
		break;
	case 2:
		moveLeftDown(way);
		break;
	case 3:
		moveLeftUp(way);
		break;
	default:
		break;
	}

	timerSprite += _deltaTime;
	if (timerSprite >= 0.2f)
	{
		sprite->Next(0, 4);
		timerSprite = 0;
	}
	
}

void Medusa::moveRightDown(int &way) {
	if (position.y >= limitBot) {
		position.x += (velocity.x * _deltaTime);
		position.y += (-velocity.y * _deltaTime);
		count++;
	}
	else {
		count = 0;
		way++;
	}
}

void Medusa::moveRightUp(int &way) {
	if (position.y <= limitTop) {
		position.x += (velocity.x * _deltaTime);
		position.y += (velocity.y * _deltaTime);
		count++;
	}
	else {
		count = 0;
		way++;
	}
}
void Medusa::moveLeftDown(int &way) {
	if (position.y >= limitBot) {
		position.x += (-velocity.x * _deltaTime);
		position.y += (-velocity.y * _deltaTime);
		count++;
	}
	else {
		count = 0;
		way++;
	}
}
void Medusa::moveLeftUp(int &way) {
	if (position.y <= limitTop) {
		position.x += (-velocity.x * _deltaTime);
		position.y += (velocity.y * _deltaTime);
		count++;
	}
	else {
		count = 0;
		way = 0;
	}
}
void Medusa::Render()
{
	sprite->Render(position.x, position.y);
}

void Medusa::Destroy()
{
	// hang 1
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x - 32, position.y + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x + 32, position.y + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	// hang 2
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x - 32, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x + 32, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	// hang 3
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x - 32, position.y - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x + 32, position.y - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	manager->Simon->score += 3000;
	isActive = false;

	// tạo item add vào world
	Item* newItem = Item::CreateItem(CRYSTAL, this->position.x, this->position.y, spriteHandler, manager);
	manager->groupItem->AddObject(newItem);
}

void Medusa::Collision()
{
	Enemy::Collision();
}

void Medusa::CheckActive()
{
	if (manager->Simon->position.x < 600 && manager->Simon->position.x>1000) //zone từ 600 - 1000, bắt đầu hành động khi simon còn cách 200
		isActive = true;
}
