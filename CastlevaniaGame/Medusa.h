#pragma once
#pragma once
#ifndef _MEDUSA_H_
#define _MEDUSA_H_

#include "Enemy.h"
#include "Snake.h"
#include <map>

class Medusa :
	public Enemy

{
public:
	int limitTop;
	int limitBot;
	int limitRight;
	int limitLeft;
	int maxCount = 900;
	int way = 0;
	int count = 0;
	bool isShown;
	float timePause, timeWait;
	float _deltaTime;
	double a;
	bool isAttack;
	Snake** list_snakes;
	int number_snakes;
	
	int oriY;
	bool isSleep;
	Medusa();
	Medusa(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Medusa();
	void isSimonNear();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
	void setSprite();
	virtual void CheckActive();
	void checkShow();
};
#endif // !_MEDUSA_H_