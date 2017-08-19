#pragma once
#pragma once
#ifndef _MEDUSA_H_
#define _MEDUSA_H_

#include "Enemy.h"

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
	float timePause;
	float _deltaTime;
	double a;
	bool isAttack;
	
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


	void moveRightDown();
	void moveRightUp();
	void moveLeftDown();
	void moveLeftUp();

	void moveZicZac();
	void setSprite();
	virtual void CheckActive();
	void checkShow();
};
#endif // !_MEDUSA_H_