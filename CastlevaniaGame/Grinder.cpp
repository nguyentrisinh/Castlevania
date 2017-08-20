#include "Grinder.h"

Grinder::Grinder(LPD3DXSPRITE _SpriteHandler, World *_manager) : Zone(_SpriteHandler, _manager)
{
	this->manager = _manager;
	this->typeZone = ZONE_GRINDER;
	this->sizeHeight = 16;
	this->sizeWidth = 64;
	this->collider = new Collider();
	this->collider->setCollider(5, -5, -29, 29);
	this->isActive = false;
	this->sprite = new Sprite(_SpriteHandler, "Resources\\Sprites\\grinder.bmp", sizeWidth, sizeHeight, 1, 1);
	this->sprite->_Index = 0;
	this->sizeWidth = 16;
	this->spriteTop = new Sprite(_SpriteHandler, "Resources\\Sprites\\grinder_top.bmp", sizeWidth, sizeHeight, 1, 1);
	this->spriteTop->_Index = 0;
	this->isLifting = false;
	this->numCount = 1;
}

Grinder::~Grinder()
{

}


// Init function 
void Grinder::Init(int _X, int _Y, int _Width, int _Height,// rect
	int _triggerX, int _triggerY,	// trigger tại vị trí này
	int param7, int param8, int _maxCount)
{
	this->isActive = true; 
	this->position.x = _X;
	this->pylonY = _Y;
	this->maxCount = _maxCount;
	
	// Công thức để tính positionY thật sự của grinder
	// posY = điểm cao nhất của grinder (cái giá treo của grinder) - 
	// số spriteTop (cột treo grinder) * sizeHeight (chiều cao của cái spriteTop) - 
	// sizeHeight / 2 (nửa chiều cao của cái grinder)
	positionY = this->pylonY - this->sizeHeight * this->numCount - this->sizeHeight / 2;
}

void Grinder::Render()
{
	if (!this->isActive)
		return;

	int postY; // Biến này để xác định postY của từng spriteTop;

	for (int i = 0; i < this->numCount; i++)
	{
		postY = this->pylonY - this->sizeHeight * i - this->sizeHeight;
		this->spriteTop->Render(this->position.x, postY);
	}

	this->sprite->Render(this->position.x, this->positionY);
}

void Grinder::Update(const float &_DeltaTime)
{

}

void Grinder::Collision(Player *actor, const float &_DeltaTime)
{

}