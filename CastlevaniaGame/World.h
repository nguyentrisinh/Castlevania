#ifndef _WORLD_H_
#define _WORLD_H_
#include "abstract/Player.h"
#include "Whip.h"
#include "enemies/Ghoul.h"
#include "enemies/RedBat.h"
#include "enemies/BlueBat.h"
#include "enemies/Panther.h"
#include "enemies/Fish.h"
#include "enemies/Knight.h"

//change Stage
#include "zone\GateWay.h"

class World
{
public:
	LPD3DXSPRITE spriteHandler;
	MainGame *castlevania;

	Sprite *background;
	
	Player *Simon;
	//GameObject *Ground;

	Whip *whip;
	Ghoul *ghoul;
	RedBat *redBat;
	BlueBat *blueBat;
	Panther *panther;
	Fish *fish;
	Knight *knight;

	//object to change stage
	GateWay *castleDoor;


	int isPause;
	float timer;
	int local; //bien random vi tri cua cá

	World(LPD3DXSPRITE _SpriteHandler, MainGame *_MainGame);
	~World();

	void Init();
	void Update(float _DeltaTime);
	void Render();
	void Destroy();

	void UpdateCreep(float _DeltaTime);
};


#endif // !_WORLD_H_
