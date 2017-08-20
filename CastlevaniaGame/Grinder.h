#ifndef _GRINDER_H_
#define _GRINDER_H_

#include "Zone.h"
#include "Player.h"

class Grinder : 
	public Zone
{
public:
	Sprite* spriteTop;
	bool isLifting;
	int numCount;
	int pylonY; // Biến này dùng để xác định vị trí cao nhất của máy nghiền (position.y của cái spriteTop cao nhất)
	int maxCount; // Biến này để xác định số sprite top tối đa của 
	int positionY; // Biến này thể hiện vị trí thật sự của cái grinder 


	Grinder(LPD3DXSPRITE _SpriteHandler, World *_manager);
	~Grinder();

	virtual void Init(int _X, int _Y, int _Width, int _Height,// rect
		int _triggerX, int _triggerY,	// trigger tại vị trí này
		int param7, int param8, int _maxCount);
	virtual void Update(const float &_DeltaTime);
	virtual void Render();
	virtual void Collision(Player *Simon, const float &_DeltaTime);
};


#endif // !_GRINDER_H_
