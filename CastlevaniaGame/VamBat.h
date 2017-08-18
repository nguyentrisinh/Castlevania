#pragma once
#ifndef _VAMBAT_H_
#define _VAMBAT_H_

#include "Enemy.h"

class VamBat :
	public Enemy

{
public:
	bool isSleep;
	float timerPause;
	VamBat();
	VamBat(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~VamBat();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	virtual void CheckActive();
	virtual void TakeDamage(int damage);
};
#endif // !_VAMBAT_H_