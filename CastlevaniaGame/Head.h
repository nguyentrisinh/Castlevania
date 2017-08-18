#ifndef _HEAD_H_
#define _HEAD_H_

#include "Enemy.h"

class Head :
	public Enemy
{
public:
	float delta;
	float lineY;

	Head();
	Head(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Head();
	virtual void Init(int _X, int _Y);
	virtual void Init(int _X, int _Y, bool isRight);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	virtual void CheckActive();
};
#endif