#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "GameObject.h"

//class này chưa được sử dụng trong project
class Effect :
	public GameObject

{
public:


	Effect();
	Effect(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Effect();
	virtual void Init(int _X, int _Y);
	virtual void Update(const int &_deltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
};
#endif // !_EFFECT_H_


