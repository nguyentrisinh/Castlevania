#include "WhipUpgrade.h"
#include "World.h"

WhipUpgrade::WhipUpgrade() {}

WhipUpgrade::WhipUpgrade(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ITEM_TYPE;
	itemType = WHIPUPGRADE;
	sizeWidth = 64;
	sizeHeight = 64;

	collider = new Collider();
	velocityY = -80;
	isActive = false;
	sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\bonus.bmp", sizeWidth, sizeHeight, 22, 6);
}

WhipUpgrade :: ~WhipUpgrade()
{

}

void WhipUpgrade::Init(int _X, int _Y)
{
	isActive = true;
	timeSurvive = 0;
	postX = _X;
	postY = _Y;
	collider->setCollider(14, -14, -14, 14);
	sprite->Next(7, 7);
}


void WhipUpgrade::Update(const float &_DeltaTime)
{
	timeSurvive += _DeltaTime;
	if (timeSurvive >= 3.0f)
		isActive = false;
	if (velocityY == 0)
		return;
	if (isActive)
	{
		postY += velocityY * _DeltaTime;

		timerSprite += _DeltaTime;
		if (timerSprite >= 0.2f)
		{
			sprite->Next(7, 7);
			timerSprite = 0;
		}
		//Khi chạm nền thì dừng lại
		if (Item::CheckGroundCollision(manager, _DeltaTime))
			velocityY = 0;
	}


}

void WhipUpgrade::Render()
{
	if (isActive)
		sprite->Render(postX, postY);
}

void WhipUpgrade::Destroy()
{
	isActive = false;
}

void WhipUpgrade::Collision(Player *player)
{
	isActive = false;
	// --------- update by K
	/*if (player->weaponLevel < 3)
		player->weaponLevel++;*/
	if (manager->whip->whipLevel < 2)
		manager->whip->whipLevel++;
}