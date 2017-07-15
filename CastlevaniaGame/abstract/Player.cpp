#include "Player.h"

// === CONSTRUCTOR === DESTRUCTOR ===
Player::Player(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = PLAYER_TYPE;
	collider = new Collider(objectType);

	sizeWidth = 64;
	sizeHeight = 64;

	isRight = true;
	isJump = false;
	downJump = false;
	isCrouch = false;
	isAttack = false;
	isHitted = false;
	isImmortal = false;
	killingMoment = false;
	isShocked = false;
	isChangeFrame = false;

	onStair = 0;

	//upKey = false;
	
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\simon_left.bmp", sizeWidth, sizeHeight, 27, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\simon_right.bmp", sizeWidth, sizeHeight, 27, 6);
	sprite = spriteRight;

	// mấy cái dưới hơi thừa, để cho toàn vẹn
	invincibleTimer = 0;

	weaponLevel = 1;
	weaponPosY = -2;// animate weapon at postY - 2
	weaponNumber = 1;

	heart = 5;
	health = 16;
	postY = 94;
}


Player::~Player()
{
	if (spriteLeft != NULL)
	{
		delete spriteLeft;
	}
	if (spriteRight != NULL)
	{
		delete spriteRight;
	}
}

// ===== VIRTUAL =====
void Player::Init(int _X, int _Y)
{
	// testing only
	tempGround = 94;

	// main init
	isActive = true;
	isRight = true;
	isImmortal = false;
	isJump = false;
	downJump = false;
	isCrouch = false;
	isAttack = false;
	isStationary = true;
	isChangeFrame = false;
	killingMoment = false;
	onStair = 0;
	//upKey = false;
	

	invincibleTimer = 0;

	postX = _X;
	postY = _Y;

	weaponLevel = 1;
	weaponPosY = -2;
	weaponNumber = 1;

	heart = 5;
	health = 16;
}

// ---=== THE MAIN PROCESSING ===---
void Player::Update(const float &_DeltaTime)
{
	
	if (isImmortal)
	{
		timerSprite += _DeltaTime;
		if (timerSprite > IMMORTAL_TIME)
			isImmortal = false;
	}

	if (isHitted)
	{
		isAttack = false;
	}

	if (isAttack)
	{
		if (postY < tempGround)
			postY = tempGround;
		timerSprite += _DeltaTime;
		//truong hop ngoi danh
		if (isCrouch)
		{
			if (timerSprite >= ANIM_TIME)
			{
				timerSprite -= ANIM_TIME;
				sprite->Next(14, 17);
				if (sprite->_Index == 16)
					killingMoment = true;
				else
					killingMoment = false;
			}
			if (sprite->_Index == 17)
			{
				isAttack = false;
				sprite->_Index = 4;
			}
		}

		else // truong hop dung danh
		{
			if (timerSprite >= ANIM_TIME)
			{
				timerSprite -= ANIM_TIME;
				sprite->Next(11, 14);
				if (sprite->_Index == 13)
					killingMoment = true;
				else
					killingMoment = false;
			}
			if (sprite->_Index == 14)
			{
				isAttack = false;
				sprite->_Index = 0;
			}
		}
	}
	else
		postX += (velocityX * _DeltaTime);


	velocityY += -(1000 * _DeltaTime);
	postY += (velocityY * _DeltaTime);
	if (isJump)
	{
		if (velocityY > 0)
		{
			//sprite->Next(4, 4);
		}
		else if (downJump)
		{
			downJump = false;
			postY -= 10;
			if(!isAttack)
			{
				sprite->Next(0, 0);
				collider->top = 28;
			}
				
		}
	}

	if (postY < tempGround)
	{
		postY = tempGround;
		isJump = false;
		if (isHitted)
		{
			isHitted = false;
			isImmortal = true;
			if(!isAttack)
				sprite->_Index = 0;
			timerSprite = 0;
		}

		velocityY = 0;
	}

	//sprite->Next(0, 0);
	

	
	/*else
	{
		if (velocityX != 0)
		{
			timerSprite += _DeltaTime;
			if (timerSprite > ANIM_TIME)
			{
				timerSprite -= ANIM_TIME;
				sprite->Next(0, 3);
			}
		}
	}*/
	
	



	/*
	if (onStair == 1)
		sprite->Next(7, 8);
	if (onStair == -1)
		sprite->Next(5, 6);*/


	//////////
	Sprite::cameraX = postX - 256;
	if (Sprite::cameraX < Sprite::cameraXLeft)
	{
		Sprite::cameraX = Sprite::cameraXLeft;
	}
	else if (Sprite::cameraX > Sprite::cameraXRight)
	{
		Sprite::cameraX = Sprite::cameraXRight;
	}
}

void Player::Render()
{
	sprite->Render(postX, postY);
}

void Player::Destroy() {}

void Player::Collision() {}

void Player::Move(int moveKey, const float &_DeltaTime)

{
	if (isJump)
		return;
	if (isAttack)
		return;
	if (isHitted)
		return;

	if (onStair == 0)
	{
		switch (moveKey)
		{
		case -1:
			velocityX = -70;
			isRight = false;
			sprite = spriteLeft;
			break;
		case 1:
			velocityX = 70;
			isRight = true;
			sprite = spriteRight;
			break;
		default:
			velocityX = 0;
			sprite->Next(0, 0);
			break;
		}

		if (velocityX != 0)
		{
			timerSprite += _DeltaTime;
			if (timerSprite > ANIM_TIME)
			{
				timerSprite -= ANIM_TIME;
				sprite->Next(0, 3);
			}
		}

	}
	
}

void Player::Up(int upKey)
{
	/*onStair = 1;
	switch (upKey)
	{
	case -1:
		velocityX = -0.2;
		velocityY = 0.2;
		isRight = false;
		sprite = spriteLeft;
		break;
	case 1:
		velocityX = 0.2;
		velocityY = 0.2;
		isRight = true;
		sprite = spriteRight;
		break;
	}*/
}

void Player::Down(int downKey)
{
	if (onStair)
	{
		return;
		// changed in future
	}
	if (isJump)
	{
		return;
	}
	if (isAttack)
	{
		return;
	}
	if (isHitted)
	{
		return;
	}

	if (downKey == 0)
	{
		isCrouch = false;
		collider->top = 28;
		weaponPosY = -2;
	}
	else
	{
		isCrouch = true;
		collider->top = 14;
		weaponPosY = -16;

		if (isRight)
			sprite = spriteRight;
		else
			sprite = spriteLeft;
		sprite->Next(4, 4);
	}

	/*
	onStair = -1;
	switch (downKey)
	{
	case -1:
		velocityX = -0.2;
		velocityY = -0.2;
		isRight = false;
		sprite = spriteLeft;
		break;
	case 1:
		velocityX = 0.2;
		velocityY = -0.2;
		isRight = true;
		sprite = spriteRight;
		break;
	}*/
}

void Player::Jump()
{
	if (isHitted)
		return;

	if (!isJump)
	{
		isJump = true;
		downJump = true;
		postY += 10;
		velocityY = 410;
		sprite->Next(4, 4);
		collider->top = 14;
	}
}

void Player::Attack()
{
	if (isAttack)
		return;
	isAttack = true;
	timerSprite = 0;
}

void Player::Injured()
{
	if (isAttack)
		return;
	if (isImmortal)
		return;
	if (isHitted)
		return;
	velocityY = 300;
	isHitted = true;
	sprite->Next(9, 9);
	if (isRight)
	{
		velocityX = -80;
	}
	else
		velocityX = 80;
}
	
