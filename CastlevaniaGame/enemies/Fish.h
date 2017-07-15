#ifndef _FISH_H_
#define _FISH_H_

#include "../abstract/Enemy.h"

class Fish :
	public Enemy

{
public:
	int health;

	// trang thai nhay tu nuoc len
	bool jumping;
	
	// trang thaìi con caì mõÒ miêòng bãìn
	float isFiring;
	float timer;
	
	Fish();
	Fish(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Fish();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Update(float _X, float _Y);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();

	virtual void Init(int _X, int _Y, bool isRight);
	virtual void CheckActive();
};
#endif // !_FISH_H_


