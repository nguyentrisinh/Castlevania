#include "Fish.h"
#include "Sprite.h"
#include "World.h"
#include <time.h>

Fish::Fish() {}

Fish::Fish(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(22, -32, -13, 13);
	enemyType = FISH;

	isFiring = false;
	timer = 5;
	sprite->_Index = 12;
	spriteRight->_Index = 12;

}

Fish :: ~Fish()
{

}

void Fish::Init(int _X, int _Y)
{
	health = 1;

	isFiring = false;
	TimeToAttack = 0;
	isActive = true;
	position.y = 0;
	velocity.y = 650;
	position.x = _X;


	if (position.x > manager->Simon->position.x)
	{
		velocity.x = -70;
		sprite = spriteLeft;
	}
	else
	{
		velocity.x = 70;
		sprite = spriteRight;
	}

	jumping = true;
}

//chỉ xài hàm này
void Fish::Init(int _X, int _Y, bool isRight)
{
	Game::gameSound->playSound(UPWATER);
	health = 1;
	damage = 1;

	isFiring = false;
	TimeToAttack = 5;
	isActive = true;
	position.y = 0;
	velocity.y = 650;

	do
	{
		position.x = Sprite::cameraX + 31 + (rand() % 450);
	} while ((position.x > (manager->Simon->position.x - 100)) && (position.x < (manager->Simon->position.x + 100)));


	if (position.x > manager->Simon->position.x)
	{
		velocity.x = -70;
		sprite = spriteLeft;
	}
	else
	{
		velocity.x = 70;
		sprite = spriteRight;
	}

	jumping = true;

	Effect* bubble1 = Effect::CreateEffect(EFFECT_BUBBLE, position.x, position.y + 20, -4, spriteHandler, manager);
	manager->groupEffect->AddObject(bubble1);
	Effect* bubble2 = Effect::CreateEffect(EFFECT_BUBBLE, position.x, position.y + 40, -2, spriteHandler, manager);
	manager->groupEffect->AddObject(bubble2);
	Effect* bubble3 = Effect::CreateEffect(EFFECT_BUBBLE, position.x, position.y + 20, 1, spriteHandler, manager);
	manager->groupEffect->AddObject(bubble3);

}

void Fish::Update(const float &_DeltaTime)
{
	if (!isActive)
		return;

	//random thoi gian doi chieu
	srand(time(NULL));
	timer = (rand() % 400 + 100) / 100.0;

	//timer = 1.5f;

	// xac dinh sprite can ve

	//xac dinh toòa do Y
	velocity.y += -(600 * _DeltaTime);

	//kiem tra neu Y huong xuong va vi?tri doi tuong thap hon mãòt ðâìt
	if (Enemy::CheckGroundCollision(manager, _DeltaTime))
	{
		velocity.y = 0;
		jumping = false;
	}
	if (!jumping)
	{
		position.x += velocity.x * _DeltaTime;

		//tinh thoi gian tan cong
		TimeToAttack += _DeltaTime;

		//luu thoi gian chuyen frame cua con ca
		timerSprite += _DeltaTime;

		//thoi gian de chuyen frame 
		if (timerSprite >= 2 * ANIM_TIME)
		{
			// kiem tra con ca co dang tan cong hay không?
			if (position.x < manager->Simon->position.x)
			{
				isRight = true;
				sprite = spriteRight;
				velocity.x = 70;
			}
			else
			{
				isRight = false;
				sprite = spriteLeft;
				velocity.x = -70;
			}

			sprite->Next(12, 13);
			//kiem tra va cho con ca tan cong
			if (TimeToAttack >= timer) // con ca khong ban lien tuc
			{
				ActivateFishFire();
				sprite->_Index = 11;
				TimeToAttack = 0;
			}
			timerSprite = 0;
		}

	}
	position.y += (velocity.y * _DeltaTime);

	if (!IsInCamera())
		this->isActive = false;
}


void Fish::Render()
{
	if (!isActive)
		return;
	sprite->Render(position.x, position.y);
}

void Fish::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 300;
	isActive = false;
}

void Fish::Collision()
{
	Enemy::Collision();
}

void Fish::CheckActive()
{
	if (position.x < Sprite::cameraXLeft || position.x > Sprite::cameraXRight)
		isActive = false;
}

void Fish::ActivateFishFire()
{
	EnemyFire *enemyFire = new EnemyFire(manager->spriteHandler, manager);
	enemyFire->Init(position.x, position.y + 17, isRight);
	manager->groupEnemy->AddObject(enemyFire);
}