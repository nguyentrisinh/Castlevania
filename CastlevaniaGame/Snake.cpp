#include "Snake.h"
#include "World.h"
#include "GroupObject.h"

Snake::Snake(LPD3DXSPRITE _SpriteHandler, World *_manager):Enemy(_SpriteHandler, _manager)
{
	manager = _manager;
	collider = new Collider();
	collider->setCollider(24, -14, 26, 72);

	position.x = 0;
	position.y = 0;
	sizeWidth = 32;
	sizeHeight = 20;
	enemyType = SNAKE;
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\snake.png", 32, 20, 2, 2);
	sprite = spriteRight;
	isActive = false;
}
Snake::~Snake()
{
	
}
void Snake::Init(int _X, int _Y, bool isRight)
{
	//Nếu simon ở bên phải thì đi qua phải
	if (isRight)
		velocity.x = 150;
	else
		velocity.x = -150; //không thì đi về trái

	limitLeft = 100;
	limitRight = 535;

	health = 1;
	damage = 1;
	
	sprite = spriteRight;
	velocity.y = -150;
	isActive = true;
	position.x = _X;
	position.y = _Y;
}

void Snake::Update(const float &_DeltaTime)
{
	_deltaTime = _DeltaTime;
	
	//Nếu rắn qua tường trái hoặc rớt xuống quá sâu thì biến mất
	if (position.x <= limitLeft || position.y <= 915) {
		isActive = false;
		return;
	}
	//Nếu chưa chạm đất rớt xuống hoặc khi đụng tường bên phải
	if (!CheckGroundCollision() || position.x >= limitRight) {
		position.y += (velocity.y * _deltaTime);
	}

	//Nếu đang ở trên đất, và bắt đầu đi
	else {
		position.x += (velocity.x * _deltaTime);
	}
	
	timerSprite += _DeltaTime;
	if (timerSprite >= 0.2f)
	{
		sprite->Next(0, 1);
		timerSprite = 0;
	}
}
void Snake::Render()
{

	if (isActive)
	{
		sprite->Render(position.x, position.y);
	}

}

void Snake::Destroy()
{
	isActive = false;
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	manager->Simon->score += 100;
}
void Snake::Collision()
{}

bool Snake::CheckGroundCollision() {

	//Check for each object in quad tree is ground and collision?
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		GameObject *object = manager->groupQuadtreeCollision->objects[i];

		switch (object->objectType)
		{
		case GROUND_TYPE:
			float collisionScale = SweptAABB(object, _deltaTime);

			if (collisionScale < 1.0f)
			{
				switch (((Ground*)object)->typeGround)
				{
				case GROUND_BLOCK:
					return true;
					break;
				default:
					break;
				}
			}
		}
	}
	return false;
}
