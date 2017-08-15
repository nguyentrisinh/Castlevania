#include "Ground.h"
#include "ColliderBlock.h"
#include "Brick.h"
#include "Bar.h"

Ground::Ground() {}

Ground::Ground(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = GROUND_TYPE;
	typeGround = 0;
	isBreakable = false;
}

Ground :: ~Ground() {}

void Ground::Init(int _X, int _Y, int param1, int param2)
{
	position.x = _X;
	position.y = _Y;
}

//
void Ground::Update(const float &_DeltaTime)
{
}

void Ground::Render()
{
	sprite->Render(position.x, position.y);
}

void Ground::Destroy()
{

}

void Ground::Collision()
{

}

Ground* Ground::CreateGround(int* parameters, LPD3DXSPRITE spriteHandler, World *manager)
{
	Ground* newGround = NULL;

	switch (parameters[1] % 100)
	{
		// khối block bình thường, đứng lên dc, tuỳ chỉnh kích thước
	case GROUND_BLOCK:
		newGround = new ColliderBlock(spriteHandler, manager);
		break;
		// các cục gạch có thể bị đập bể & rớt item
	case GROUND_BRICK1:
	case GROUND_BRICK2:
	case GROUND_BRICK3:
	case GROUND_BRICK4:
		newGround = new Brick(spriteHandler, manager, parameters[1] % 100);
		break;
		// 1 thanh ground đi qua đi lại
	case GROUND_BAR:
		newGround = new Bar(spriteHandler, manager);
		break;
	default:
		break;
	}

	if (newGround != NULL)
		newGround->Init(parameters[2], parameters[3], parameters[4], parameters[5]);

	return newGround;
}