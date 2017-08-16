#ifndef _REDBAT_H_
#define _REDBAT_H_

#include "Enemy.h"

class RedBat :
	public Enemy

{
public:
	float angle; //góc bay
	float yOgirin; // đường bay xác định lúc đầu

	RedBat();
	RedBat(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~RedBat();
	virtual void Init(int _X, int _Y);
	virtual void Init(int _X, int _Y, bool isRight);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	virtual void CheckActive();
};
#endif // !_REDBAT_H_
