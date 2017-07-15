#include "Effect.h"

Effect::Effect() {}

Effect::Effect(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	manager = _manager;
	objectType = EFFECT_TYPE;

}

Effect :: ~Effect()
{

}

void Effect::Init(int _X, int _Y)
{

}

void Effect::Update(const int &_deltaTime)
{
}

void Effect::Render()
{
	sprite->Render(postX, postY);
}

void Effect::Destroy()
{

}

void Effect::Collision()
{

}