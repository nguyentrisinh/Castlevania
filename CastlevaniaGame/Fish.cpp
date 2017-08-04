#include "Fish.h"
#include "Sprite.h"
#include "World.h"
#include <time.h>

Fish::Fish() {}

Fish::Fish(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(22, -24, -13, 13);
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
	postY = 0;
	velocityY = 450;
	postX = _X;
	if (postX > manager->Simon->postX)
	{
		velocityX = -70;
		sprite = spriteLeft;
	}
	else
	{
		velocityX = 70;
		sprite = spriteRight;
	}

	jumping = true;
}

// --- update by K
void Fish::Init(int _X, int _Y, bool isRight)
{
	health = 1;

	isFiring = false;
	TimeToAttack = 0;
	isActive = true;
	postY = 0;
	velocityY = 650;


	postX = Sprite::cameraX + 31 + (rand() % 450);

	if (postX > manager->Simon->postX)
	{
		velocityX = -70;
		sprite = spriteLeft;
	}
	else
	{
		velocityX = 70;
		sprite = spriteRight;
	}

	jumping = true;
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
	velocityY += -(600 * _DeltaTime);
	postY += (velocityY * _DeltaTime);

	//kiem tra neu Y huong xuong va vi?tri doi tuong thap hon mãòt ðâìt
	if (velocityY < 0 && postY < 224)
	{

		jumping = false;
		postY = 224;
		postX += velocityX * _DeltaTime;

		//tinh thoi gian tan cong
		TimeToAttack += _DeltaTime;

		//luu thoi gian chuyen frame cua con ca
		timerSprite += _DeltaTime;

		//thoi gian de chuyen frame 
		if (timerSprite >= 2 * ANIM_TIME)
		{
			// kiem tra con ca co dang tan cong hay không?
			if (isFiring)
			{
				if (postX < manager->Simon->postX)
					velocityX = 70;
				else
					velocityX = -70;
				isFiring = false;
				if (velocityX > 0)
					sprite = spriteRight;
				else
					sprite = spriteLeft;
			}
			else // con ca dang khong tan cong
			{
				sprite->Next(12, 13);
				//kiem tra va cho con ca tan cong
				if (TimeToAttack >= timer)
				{
					sprite->_Index = 11;
					TimeToAttack = 0;
					isFiring = true;
				}
				timerSprite = 0;
			}
		}

	}
}


void Fish::Render()
{
	if (!isActive)
		return;
	sprite->Render(postX, postY);
}

void Fish::Destroy()
{
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, postX, postY, -1, spriteHandler, manager);
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
	if (postX < Sprite::cameraXLeft || postX > Sprite::cameraXRight)
		isActive = false;
}