#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "GameObject.h"
#include "Game.h"

#define REDBAT 1
#define BLUEBAT 2
#define GHOUL 3
#define FISH 4
#define PANTHER 5
#define ENEMYFIRE 6
#define VAMBAT 7
#define MEDUSA 8
#define SNAKE 9
#define HEAD 11
#define BONE 13

class Enemy :
	public GameObject

{
public:
	int health;
	int enemyType;
	int damage;

	bool isDamage;

	Sprite *spriteLeft;
	Sprite *spriteRight;
	Sprite *spriteVamBat;
	Sprite *spriteMedusa;
	Enemy();
	Enemy(LPD3DXSPRITE _SpriteHandler, World *_manager);
	virtual ~Enemy();

	virtual void Init(int _X, int _Y);
	virtual void Init(int _X, int _Y, bool _IsRight);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
	virtual void TakeDamage(int Damage);
	//ham ao moi tao
	virtual void CheckActive();
	void TakeDamage(GameObject* actor, int damage);
	static Enemy* CreateEnemy(int type, int X, int Y, LPD3DXSPRITE _SpriteHandler, World *_manager);
	bool CheckGroundCollision(World *manager, const float _DeltaTime);
	static Enemy* CreateEnemy(int* parameters, LPD3DXSPRITE spriteHandler, World *manager);
};
#endif // !_ENEMY_H_

