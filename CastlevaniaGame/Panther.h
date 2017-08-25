#ifndef _PANTHER_H_
#define _PANTHER_H_

#include "Enemy.h"

class Panther :
	public Enemy

{
public:
	static int index;
	float distanceToSimon;
	int distanceToSimonY;
	int limitTop;
	int limitDown;
	int oriX;
	int state; //0: runningLeft, 1: jumping, 2: downing, 3: runningRight
	float _deltaTime;
	World *_manager;
	bool isSleeping;
	bool hasJumped;
	bool isRight;
	int startX;
	int startY;
	Panther();
	Panther(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Panther();
	virtual void Init(int _X, int _Y);
	void Init(int _X, int _Y, bool _isRight);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
	void setSprite();
	void runningLeft();
	void jumping();
	void downing();
	void moving();
	void runningRight();
	virtual void CheckActive();
	bool CheckGroundCollision();
	bool isInCamera();
};
#endif // !_PANTHER_H_

