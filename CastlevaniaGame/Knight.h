#ifndef _KNIGHT_
#define _KNIGHT_

#include "Enemy.h"

class Knight :
	public Enemy

{
public:
	static int index;
	float timerFrozen;
	int limitLeft;
	int limitRight;
	World *_manager;
	float _deltaTime;
	int startX, startY;
	bool isSleeping;
	bool isFrozen;
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
	bool isInCamera();
	void TakeDamage(int damage);
};
#endif // !_Knight_H_

