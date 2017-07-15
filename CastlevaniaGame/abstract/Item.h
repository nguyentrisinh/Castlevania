#ifndef _ITEM_H_
#define _ITEM_H_

#include "GameObject.h"

class Item :
	public GameObject

{
public:
	int health;

	Sprite *spriteLeft;
	Sprite *spriteRight;
	Item();
	Item(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Item();
	virtual void Init(int _X, int _Y);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Destroy();
	virtual void Collision();
};
#endif // !_Item_H_

