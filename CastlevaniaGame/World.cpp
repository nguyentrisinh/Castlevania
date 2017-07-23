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

	Simon->Init(70, 120);

	//Init object to change screen
	castleDoor = new GateWay(spriteHandler, this);
	castleDoor->Init(128, 64, 1024, 1086, 100, 560, 32, 5408, 896);
}

// gọi ở đầu game_run
void World::Update(float _DeltaTime)
{
	Simon->Update(_DeltaTime);

	//Update condition Simon collide with gateway and change the stage
	if (Simon->isCollide(castleDoor))
	{
		if ((castleDoor->objectType) == ZONE_TYPE)
		{
			castleDoor->Collision(Simon, _DeltaTime);
		}
	}
	//---------------------------------------

	
	UpdateCreep(_DeltaTime);
}

void World::UpdateCreep(float _DeltaTime)
{

	// update quái nếu nó sống  ||| và tạo lại nếu nó chết rồi

	if (ghoul->isActive)
	{
		ghoul->Update(_DeltaTime);

		if (ghoul->isCollide(Simon) && !Simon->isImmortal)
			Simon->Injured();
		if (Simon->isAttack && Simon->killingMoment)
			if (ghoul->isCollide(whip))
				ghoul->isActive = false;
	}
	else
	{
		if (Simon->isRight)
			ghoul->Init(Sprite::cameraXRight, 94, Simon->isRight);
		else
			ghoul->Init(Sprite::cameraXLeft, 94, Simon->isRight);
	}


	if (redBat->isActive)
	{
		redBat->Update(_DeltaTime);

		if (redBat->isCollide(Simon) && !Simon->isImmortal)
		{
			Simon->Injured();
			redBat->isActive = false;
		}

		if (Simon->isAttack && Simon->killingMoment)
			if (redBat->isCollide(whip))
				redBat->isActive = false;
	}
	else
	{
		if (Simon->isRight)
			redBat->Init(Sprite::cameraXRight, Simon->position.y, Simon->isRight);
		else
			redBat->Init(Sprite::cameraXLeft, Simon->position.y, Simon->isRight);
	}

	if (blueBat->isActive)
	{
		blueBat->Update(_DeltaTime);

		if (blueBat->isCollide(Simon) && !Simon->isImmortal)
		{
			Simon->Injured();
			blueBat->isActive = false;
		}

		if (Simon->isAttack && Simon->killingMoment)
			if (blueBat->isCollide(whip))
				blueBat->isActive = false;
	}
	else
	{
		if (Simon->isRight)
			blueBat->Init(Sprite::cameraXRight, Simon->position.y + 60, Simon->isRight);
		else
			blueBat->Init(Sprite::cameraXLeft, Simon->position.y + 60, Simon->isRight);
	}

	if (panther->isActive)
	{
		panther->Update(_DeltaTime);

		if (panther->isCollide(Simon) && !Simon->isImmortal)
			Simon->Injured();
		if (Simon->isAttack && Simon->killingMoment)
			if (panther->isCollide(whip))
				panther->isActive = false;
	}
	else
	{
		if (Simon->isRight)
			panther->Init(Sprite::cameraXRight, 94, Simon->isRight);
		else
			panther->Init(Sprite::cameraXLeft, 94, Simon->isRight);
	}

	if (fish->isActive)
	{
		fish->Update(_DeltaTime);


		if (fish->isCollide(Simon) && !Simon->isImmortal)
			Simon->Injured();
		if (Simon->isAttack && Simon->killingMoment)
			if (fish->isCollide(whip))
				fish->isActive = false;
	}
	else
	{
		local = (rand() % Sprite::cameraXRight + Sprite::cameraXLeft) / 2;
		fish->Init(local, 94, Simon->isRight);
	}



}

// gọi ở cuối game_run, bên trong BeginScene() và EndScene();
void World::Render()
{

	if (ghoul->isActive)
	{
		ghoul->Render();
	}


	if (redBat->isActive)
	{
		redBat->Render();
	}

	if (blueBat->isActive)
	{
		blueBat->Render();
	}

	if (panther->isActive)
	{
		panther->Render();
	}

	if (fish->isActive)
	{
		fish->Render();
	}

	Simon->Render();


	//The whip
	if (Simon->isAttack && Simon->sprite->_Index >= 11)
	{
		if (Simon->isCrouch)
			whip->Render(Simon->position.x, Simon->position.y - 14, (Simon->sprite->_Index - 3), Simon->isRight);
		else
			whip->Render(Simon->position.x, Simon->position.y, Simon->sprite->_Index, Simon->isRight);
	}


	//Render GateWay to change stage
	castleDoor->Render();
	//------------------------



}

void World::Destroy()
{

}
