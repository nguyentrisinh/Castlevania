#ifndef _KNIGHT_
#define _KNIGHT_

#include "Enemy.h"

class Knight :
	public Enemy

{
public:
	static int index;
	int limitLeft;
	int limitRight;
	World *_manager;
	float _deltaTime;
	int startX, startY;
	bool isSleeping;
	Knight();
	Knight(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Knight();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
	virtual void CheckActive();
	void notMovingThroughWall();
	void setSprite();
	bool CheckGroundCollision();
	int checkWallCollision();
	void TakeDamage(int Damage);
};
#endif // !_Knight_H_

