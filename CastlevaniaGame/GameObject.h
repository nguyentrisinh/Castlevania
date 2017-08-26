//======= GAMEOBJECT ========
// cho kế thừa muôn nơi

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <d3dx9.h>
#include "Sprite.h"
#include "Misc.h"

#include <cstdlib>
#include <ctime>

//#include <math.h>

#define PLAYER_TYPE 1
#define PROJECTILE_TYPE 2
#define EFFECT_TYPE 3
#define ITEM_TYPE 4
#define ENEMY_TYPE 5
#define DESTRUCTIBLE_TYPE 6
#define GROUND_TYPE 7
#define STAIR_TYPE 8
#define ZONE_TYPE 9

#define ANIM_TIME 0.15f
#define ITEM_TIME 2.0f
#define IMMORTAL_TIME 3.0f

#define PI 3.141592f
#define val PI/180


class GameObject
{
public:
	// các biến
	World *manager;
	LPD3DXSPRITE spriteHandler;
	bool isActive;
	int objectType;

	int sizeWidth;
	int sizeHeight;

	Sprite *sprite;
	float timerSprite;

	Collider *collider;

	D3DXVECTOR2 position;

	D3DXVECTOR2 velocity;

	float normalx;
	float normaly;

	Collider *BroadPhaseBox;
	float collisionTimeScale;

	// constructor và destructor
	GameObject();
	virtual ~GameObject();

	D3DXVECTOR3 VecCollide(GameObject *target);

	bool IsCollide(GameObject* target);
	bool IsInside(GameObject* target);
	bool IsInCamera();

	float SweptAABB(GameObject *target, const float &_DeltaTime);

	void ResponseFrom(GameObject *target, const float &_DeltaTime, const float &_CollisionTimeScale);
	void DeflectFrom(GameObject *target, const float &_DeltaTime, const float &_CollisionTimeScale);
	void PushFrom(GameObject *target, const float &_DeltaTime, const float &_CollisionTimeScale) {};
	void SlideFromGround(GameObject *target, const float &_DeltaTime, const float &_CollisionTimeScale);

	virtual void Init(int _X, int _Y);		
	virtual void Update(const float &_DeltaTime);	
	virtual void Render();							
	virtual void Destroy();					

	virtual void Collision();

	virtual void CollisionObject(GameObject *target, const float &_DeltaTime);

	//Bổ trợ làm hiệu ứng lấp lánh (Hit)
	int RandomOutside(int radiusSmall, int radiusBig);
};



#endif