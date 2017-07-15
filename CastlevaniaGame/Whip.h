#ifndef _WHIP_H_
#define _WHIP_H_

#include "abstract/Projectile.h"

class Whip :
	public Projectile
{
public:
	Whip(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Whip();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
	void Update(float X, float Y);
	void Render(float X, float Y, int simonIndex, bool isRight);

};

#endif // !_WHIP_H_


