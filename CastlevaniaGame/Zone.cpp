#include "Zone.h"
#include "GateWay.h"
#include "StandItem.h"
#include "DeadZone.h"
#include "Spawner.h"
#include "BattleBoss.h"
#include "Grinder.h"

Zone::Zone(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = ZONE_TYPE;
	typeZone = 0;	// for sub class
	collider = new Collider();
}

Zone :: ~Zone()
{

}

// ----- update K_1.9
void Zone::Init(int _X, int _Y, int _Width, int _Height)
{
	position.x = _X;
	position.y = _Y;

	collider->top = _Height / 2;
	collider->bottom = -collider->top;
	collider->right = _Width / 2;
	collider->left = -collider->right;
}

void Zone::Init(int _X, int _Y, int _Width, int _Height,// rect
	int _triggerX, int _triggerY,	// trigger tại vị trí này
	int param7, int param8, int param9) {}
// --------------

void Zone::Update(const float &_DeltaTime)
{
	// không có gì để update cả
}

void Zone::Render()
{
	// chẳng có gì để update luôn
}

void Zone::Destroy()
{

}

void Zone::Collision(Player *actor, const float &_DeltaTime)
{
	// virtual
}

Zone* Zone::CreateZone(int* parameters, LPD3DXSPRITE spriteHandler, World *manager)
{
	Zone* newZone = NULL;

	switch (parameters[1] % 100)
	{
		// đụng vào đây là dịch chuyển
	case ZONE_GATEWAY:
		newZone = new GateWay(spriteHandler, manager);
		break;
		// chuyên thả item
	case ZONE_STAND:
	case ZONE_CROUCH:
		newZone = new StandItem(spriteHandler, manager);
		break;
	case ZONE_SPAWNER:
		newZone = new Spawner(spriteHandler, manager);
		break;
	case ZONE_DEAD:
		newZone = new DeadZone(spriteHandler, manager, parameters[1] % 100);
		break;
	case ZONE_GRINDER:
		//newZone = new DeadZone(spriteHandler, manager, parameters[1] % 100);
		newZone = new Grinder(spriteHandler, manager);
		break;
	case ZONE_BATTLEBOSS:
		newZone = new BattleBoss(spriteHandler, manager);
		break;
	default:
		break;
	}

	// tổng cộng Zone cần đến 11 paramaters
	if (newZone != NULL)
		newZone->Init(parameters[2], parameters[3], parameters[4], parameters[5]
			, parameters[6], parameters[7]
			, parameters[8], parameters[9], parameters[10]);


	return newZone;
}