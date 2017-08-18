#include "Panther.h"
#include "Sprite.h"
#include "World.h"

Panther::Panther() {}

Panther::Panther(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -32, -14, 14);
	enemyType = PANTHER;

	// ---- update K_1.7
	spriteLeft->_Index = 2;
	spriteRight->_Index = 2;
	// ----------
	this->_manager = _manager;
}

Panther :: ~Panther()
{

}

void Panther::Init(int _X, int _Y)
{
	if (manager->Simon->position.x < _X)
		Init(_X, _Y, false);
	else
		Init(_X, _Y, true);

}

void Panther::Init(int _X, int _Y, bool _isRight) {
	isActive = true;
	isSleeping = true;
	hasJumped = false;
	position.y = _Y - 10;
	limitTop = _Y + 20;
	limitDown = position.y - 30;
	position.x = _X - 20;
	isRight = _isRight;
	state = 0;
	sprite = spriteLeft;
	velocity.x = 200;
	velocity.y = 50;
	distanceToSimon = position.x - 250;
	health = 1;
}
void Panther::moving() {
	switch (state) {
	case 0:
		runningLeft();
		break;
	case 1:
		jumping();
		break;
	case 2:
		downing();
		break;
	case 3:
		runningRight();
		break;
	default:
		break;
	}
}

void Panther::runningLeft() {
	if (!CheckGroundCollision()) {
		state++;
		return;
	}
	position.x += ((-velocity.x) * _deltaTime);
}

void Panther::jumping() {
	if (position.y >= limitTop) {
		//move to next state
		state++;
		return;
	}
	position.y += ((velocity.y * 3) * _deltaTime);
	position.x += ((-velocity.x + -100) *_deltaTime);
}

void Panther::downing() {
	if (position.y <= limitDown) {
		if (CheckGroundCollision()) {
			state++;
			return;
		}
	}
	position.y += ((-velocity.y * 5) * _deltaTime);
	position.x += ((-velocity.x + -50) * _deltaTime);
}
void Panther::runningRight() {
	position.x += ((velocity.x) * _deltaTime);
	sprite = spriteRight;
}

void Panther::Update(const float &_DeltaTime)
{
	if (manager->Simon->position.x > distanceToSimon
		&& position.x >= Sprite::cameraXLeft
		&& position.x <= Sprite::cameraXRight)
		isSleeping = false;

	if (isSleeping)
		return;
	_deltaTime = _DeltaTime;

	moving();

	setSprite();

	//kiem tra nam ngoai camera
	if (!IsInCamera())
		isActive = false;
}

void Panther::setSprite() {
	if (state == 1 || state == 2) {
		sprite->Index(4);
		return;
	}
	timerSprite += _deltaTime;

	if (timerSprite >= ANIM_TIME)
	{
		sprite->Next(3, 5);
		timerSprite = 0;
	}
}
void Panther::Render()
{
	if (isActive)
		sprite->Render(position.x, position.y);
}

void Panther::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 200;
	isActive = false;
}

void Panther::Collision()
{
	Enemy::Collision();
}

void Panther::CheckActive()
{
	if (position.x < Sprite::cameraXLeft || position.x > Sprite::cameraXRight)
		isActive = false;

}

bool Panther::CheckGroundCollision() {

	//Check for each object in quad tree is ground and collision?
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		GameObject *object = manager->groupQuadtreeCollision->objects[i];

		switch (object->objectType)
		{
		case GROUND_TYPE:
			float collisionScale = SweptAABB(object, _deltaTime);

			if (collisionScale < 1.0f)
			{
				switch (((Ground*)object)->typeGround)
				{
				case GROUND_BLOCK:
					return true;
					break;
				default:
					break;
				}
			}
		}
	}
	return false;
}