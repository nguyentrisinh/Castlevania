//======= GAMEOBJECT ========

#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <d3dx9.h>
#include "../engine/Sprite.h"
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
#define IMMORTAL_TIME 0.3f

#define PI 3.141592f
#define val PI/180


class GameObject
{
public:
	// các biến
	World *manager;

	bool isActive;
	int objectType;

	int sizeWidth;
	int sizeHeight;
		
	//LPD3DXSPRITE spriteHandler;
	Sprite *sprite;
	float timerSprite;

	Collider *collider;

	float postX;
	float postY;
	float velocityX;
	float velocityY;

	// constructor và destructor
	GameObject();
	virtual ~GameObject();

	// ====== CÁC HÀM CHÍNH ======
	// vị trí collistion (= vector0 nếu ko chạm)
	D3DXVECTOR3 vecCollide(GameObject *target);
	// xét coi có va chạm ko
	bool isCollide(GameObject *target);

	// ====== các phương thức ảo =====
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
	
};




//// ========= COLLIDER ===========
//class Collider
//	{
//	public:
//		// các biến
//		// trục Y hướng lên
//		int top;	// luôn > 0
//		int bottom;	// luôn < 0
//					// trục X hướng qua phải
//		int left;	// luôn < 0
//		int right;	// luôn > 0
//	
//		GameObject *owner;
//	
//		//Khởi tạo và huỷ
//		Collider();
//		Collider(GameObject *_owner, int _top, int _bottom, int _left, int _right)
//			:owner(_owner), top(_top), bottom(_bottom), left(_left), right(_right) {};
//		~Collider();
//	};



// ========== WORLD =============
//class World
//{
//public:
//	LPD3DXSPRITE spriteHandler;
//	Sprite *background;
//
//
//	GameObject *Simon;
//	GameObject *Ground;
//
//	int isPause;
//	int timer;
//	int deltaTime;
//
//	World(LPD3DXSPRITE _SpriteHandler);
//	~World();
//
//	void Init();
//	void Update(int _deltaTime);
//	void Render();
//	void Destroy();
//};

#endif