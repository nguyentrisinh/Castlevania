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
	isShown = false;
}

Medusa :: ~Medusa()
{

}

void Medusa::Init(int _X, int _Y)
{
	health = 16;
	isSleep = true;
	isActive = true;
	isAttack = false;
	oriY = _Y;
	position.x = _X;
	
	position.y = _Y + 100;
	limitTop = _Y;
	limitBot = _Y - 100;
	limitRight = _X + 200;
	limitLeft = _X - 200;
}
void Medusa::setSprite() {
	timerSprite += _deltaTime;
	if (timerSprite >= 0.2f)
	{
		sprite->Next(0, 4);
		timerSprite = 0;
	}
}
void Medusa::Update(const float &_DeltaTime)
{
	if (isSleep)
	{
		position.y = oriY + 120;
		if (manager->Simon->position.x <= position.x - 100) {
			isSleep = false;
			position.y = oriY;
		}	
	}
	else {
		_deltaTime = _DeltaTime;
		moveZicZac();
		setSprite();
	}
	
}

void Medusa::moveRightDown() {
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

void Medusa::moveRightUp() {
	//Move right up and not reach any limits
	if (position.y <= limitTop) {
		position.x += (velocity.x * _deltaTime);
		position.y += (velocity.y * _deltaTime);
		count++;
		return;
	}

	//Reach limit top and right, then move left down
	if (position.y > limitTop && position.x >= limitRight) {
		way++;
		return;
	}

	//Only reach limit top but not right, then move 
	way--;
	return;
}
void Medusa::moveLeftDown() {
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
void Medusa::moveLeftUp() {
	if (position.y <= limitTop) {
		position.x += (-velocity.x * _deltaTime);
		position.y += (velocity.y * _deltaTime);
		count++;
		return;
	}

	//Reach limit top and left, then move right down
	if (position.y > limitTop && position.x <= limitLeft) {
		way = 0;
		return;
	}

	//Only reach limit top but not left, then move 
	way--;
	return;
}
void Medusa::moveZicZac() {
	switch (way) {
	case 0:
		moveRightDown();
		break;
	case 1:
		moveRightUp();
		break;
	case 2:
		moveLeftDown();
		break;
	case 3:
		moveLeftUp();
		break;
	default:
		break;
	}
}
void Medusa::Render()
{
	if (!isSleep)
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
	if (position.x < Sprite::cameraXLeft || position.x > Sprite::cameraXRight)
		isActive = false;
}

void Medusa::isSimonNear() {
	if (manager->Simon->position.x <= (position.x - 150) 
		&& manager->Simon->position.y >= position.y)
		isActive = false;
}
void Medusa::checkShow() {
	if (manager->Simon->position.x <= position.x - 200)
		isShown = true;
}
