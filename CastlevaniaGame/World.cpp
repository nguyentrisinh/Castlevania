#include "World.h"
#include "engine/MainGame.h"
#include <time.h>

World::World(LPD3DXSPRITE _SpriteHandler, MainGame *_MainGame)
{
	// ---  init core  ---
	spriteHandler = _SpriteHandler;
	castlevania = _MainGame;

	// ---  init static object  ---
	Simon = new Player(spriteHandler, this);
	whip = new Whip(spriteHandler, this);
}


World::~World()
{
	
}

// 
void World::Init()
{
	// ---  init chanable object
	
	ghoul = new Ghoul(spriteHandler, this);
	redBat = new RedBat(spriteHandler, this);
	blueBat = new BlueBat(spriteHandler, this);
	panther = new Panther(spriteHandler, this);
	fish = new Fish(spriteHandler, this);

	Simon->Init(50, 150);
}

// gọi ở đầu game_run
void World::Update(float _DeltaTime)
{
	Simon->Update(_DeltaTime);
	if (ghoul->isActive)
		ghoul->Update(_DeltaTime);
	if (redBat->isActive)
		redBat->Update(_DeltaTime);
	if (blueBat->isActive)
		blueBat->Update(_DeltaTime);
	if (panther->isActive)
		panther->Update(_DeltaTime);
	if (fish->isActive)
		fish->Update(_DeltaTime);
}

// gọi ở cuối game_run, bên trong BeginScene() và EndScene();
void World::Render()
{
	//kiem tra dieu kien va render ma ca rong
	if (!ghoul->isActive)
	{
		if (Simon->isRight)
			ghoul->Init(Sprite::cameraXRight, 94, Simon->isRight);
		else
			ghoul->Init(Sprite::cameraXLeft, 94, Simon->isRight);
	}
	else
	{
		ghoul->Render();
	}

	// kiem tra dieu kien va render dơi đỏ
	if (!redBat->isActive)
	{
		if (Simon->isRight)
			redBat->Init(Sprite::cameraXRight, Simon->position.y, Simon->isRight);
		else
			redBat->Init(Sprite::cameraXLeft, Simon->position.y, Simon->isRight);
	}
	else
	{
		redBat->Render();
	}

	//kiem tra điều kiện và render dơi xanh
	if (!blueBat->isActive)
	{
		if (Simon->isRight)
			blueBat->Init(Sprite::cameraXRight, Simon->position.y + 60, Simon->isRight);
		else
			blueBat->Init(Sprite::cameraXLeft, Simon->position.y + 60, Simon->isRight);
	}
	else
	{
		blueBat->Render();
	}

	//kiem tra dieu kien va render con beo
	if (!panther->isActive)
	{
		if (Simon->isRight)
			panther->Init(Sprite::cameraXRight, 94, Simon->isRight);
		else
			panther->Init(Sprite::cameraXLeft, 94, Simon->isRight);
	}
	else
	{
		panther->Render();
	}

	//kiem tra dieu kien va render con quỷ Cá xấu xí
	if (!fish->isActive)
	{
		//srand(time(NULL));
		local = (rand() % Sprite::cameraXRight + Sprite::cameraXLeft) / 2;
		fish->Init(local, 94, Simon->isRight);
	}
	else
	{
		fish->Render();
	}

	// render nhân vật
	Simon->Render();


	//kiem tra dieu kien va render cai roi
	if (Simon->isAttack && Simon->sprite->_Index >= 11)
	{
		if (Simon->isCrouch)
			whip->Render(Simon->position.x, Simon->position.y - 14, (Simon->sprite->_Index - 3), Simon->isRight);
		else
			whip->Render(Simon->position.x, Simon->position.y, Simon->sprite->_Index, Simon->isRight);
	}

	//kiem tra hoat dong va xet va cham cua con ma ca rong
	ghoul->CheckActive();
	if (ghoul->isActive)
	{
		if (ghoul->isCollide(Simon) && !Simon->isImmortal)
			Simon->Injured();
		if (Simon->isAttack && Simon->killingMoment)
			if (ghoul->isCollide(whip))
				ghoul->isActive = false;
	}

	//kiem tra hoat dong va xet va cham cua doi do
	redBat->CheckActive();
	if (redBat->isActive)
	{
		if (redBat->isCollide(Simon) && !Simon->isImmortal)
		{
			Simon->Injured();
			redBat->isActive = false;
		}

		if (Simon->isAttack && Simon->killingMoment)
			if (redBat->isCollide(whip))
				redBat->isActive = false;
	}

	//kiem tra hoat dong va xet va cham cua doi xanh
	blueBat->CheckActive();
	if (blueBat->isActive)
	{
		if (blueBat->isCollide(Simon) && !Simon->isImmortal)
		{
			Simon->Injured();
			blueBat->isActive = false;
		}

		if (Simon->isAttack && Simon->killingMoment)
			if (blueBat->isCollide(whip))
				blueBat->isActive = false;
	}

	//kiem tra hoat dong va xet va cham cua con beo
	panther->CheckActive();
	if (panther->isActive)
	{
		if (panther->isCollide(Simon) && !Simon->isImmortal)
			Simon->Injured();
		if (Simon->isAttack && Simon->killingMoment)
			if (panther->isCollide(whip))
				panther->isActive = false;
	}

	fish->CheckActive();
	if (fish->isActive)
	{
		if (fish->isCollide(Simon) && !Simon->isImmortal)
			Simon->Injured();
		if (Simon->isAttack && Simon->killingMoment)
			if (fish->isCollide(whip))
				fish->isActive = false;
	}
	
}

void World::Destroy()
{

}
