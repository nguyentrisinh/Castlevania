#include "Medusa.h"
#include "Sprite.h"
#include "World.h"


Medusa::Medusa() {}

Medusa::Medusa(LPD3DXSPRITE _SpriteHandler, World *_manager) :Enemy(_SpriteHandler, _manager)
{
	collider->setCollider(14, -14, -12, 12);
	enemyType = MEDUSA;
	spriteMedusa = new Sprite(_SpriteHandler, "Resources\\Sprites\\medusa.png", 65, 64, 5, 5);
	sprite = spriteMedusa;
	timePause = 0;
	isAttack = false;
	velocity.y = -50;
	velocity.x = 130;
	isShown = false;

	list_snakes = new Snake*[2];
}

Medusa :: ~Medusa()
{

}

void Medusa::Init(int _X, int _Y)
{
	distanceToSimonX = 310;
	distanceToSimonY = 980;
	health = 16;
	damage = 4;
	isSleep = true;
	isActive = true;
	isAttack = false;
	oriY = _Y;
	position.x = 288;
	position.y = 1055;
	limitTop = _Y;
	limitBot = _Y - 100;
	limitRight = _X + 200;
	limitLeft = _X - 200;

	timePause = 2;
	timeWait = -1.0;
	number_snakes = 0;
	list_snakes[0] = new Snake(spriteHandler, manager);
	list_snakes[1] = new Snake(spriteHandler, manager);
	sprite->Next(4, 4);
}
void Medusa::setSprite() {
	timerSprite += _deltaTime;
	if (timerSprite >= 0.2f)
	{
		sprite->Next(0, 4);
		timerSprite = 0;
	}
}
void Medusa::Update(const float &_DeltaTime)
{
	//center: 288, 1055
	//right: 530
	//left: 130
	//bot: 980
	//top: 1070

	//Khi medusa đang ngủ
	if (isSleep)
	{
		//Vị trí nâng medusa lên để khỏi đụng simon
		position.y = 1200;
		sprite->Next(4, 4);

		//Nếu simon tới cuối cửa, thì kích hoạt đợi 4s sau đó mới wake up
		//Sau đó ko chạy đoạn này nữa
		if ((manager->Simon->position.x <= distanceToSimonX) //310
			&& (manager->Simon->position.y >= distanceToSimonY) //980
			&& (timeWait == -1.0)) //&& (manager->Simon->position.y <= position.y -250))
		{
			timeWait += _DeltaTime;
			return;
		}

		//Bắt đầu đếm tới 4s
		if (timeWait > -1.0 && timeWait <= 3.0)
		{
			timeWait += _DeltaTime;
			if (timeWait > 2.75) {
				isSleep = false;
				//Xét lại vị trí ở giữa cho medusa
				position.x = 288;
				position.y = 1055;
				velocity.y = -50;
				velocity.x = 130;
			}
			return;
		}
	}

	else {
		if (position.y < 980)
			velocity.y = 100;
		if (position.y > 1100)
			velocity.y = -100;

		if (position.x < 130)
			velocity.x = 150;
		if (position.x > 500)
			velocity.x = -150;

		timePause -= _DeltaTime;

		if (timePause <= 0.0) {
			//Cho boss đứng yên và set sprite
			velocity.x = 0;
			velocity.y = 0;
			
			timerSprite += _DeltaTime;
			if (timerSprite > ANIM_TIME)
			{
				//Sprites thả rắn
				sprite->Next(2, 3);
				timerSprite = 0;
			}

			if (timePause >= -0.5) {
				bool isRight = true;

				//Xét vị trí với Simon để xem thả rắn đi bên nào
				if (manager->Simon->position.x > position.x) {
					isRight = true;
				}
				else
				{
					isRight = false;
				}
				//Thêm rắn vào
				list_snakes[0]->Init(position.x, position.y, isRight);
				manager->groupEnemy->AddObject(list_snakes[0]);
				return;
			}

			if (timePause >= -1.0) {
				bool isRight = true;

				//Xét vị trí với Simon để xem thả rắn đi bên nào
				if (manager->Simon->position.x > position.x) {
					isRight = true;
				}
				else
				{
					isRight = false;
				}

				//Thêm rắn vào
				list_snakes[1]->Init(position.x, position.y, isRight);
				manager->groupEnemy->AddObject(list_snakes[1]);
				return;
			}

			if (timePause >= -1.5) {
				timePause = 2.5;
				if (manager->Simon->position.x > position.x) {
					velocity.x = 150;
				}
				else
					velocity.x = -150;
				velocity.y = 100;
				return;
			}
		}
		else {
			timerSprite += _DeltaTime;
			if (timerSprite > ANIM_TIME)
			{
				//Sprites lúc chạy
				sprite->Next(0, 1);
				timerSprite = 0;
			}

			position.y += velocity.y * _DeltaTime;
			position.x += velocity.x * _DeltaTime;
		}
		
	}

}


void Medusa::Render()
{
	if (!isSleep)
		sprite->Render(position.x, position.y);
	else
		sprite->Render(position.x, 1055);
}

void Medusa::Destroy()
{
	// hang 1
	Effect* effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x - 32, position.y + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x + 32, position.y + 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	// hang 2
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x - 32, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x + 32, position.y, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	// hang 3
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x - 32, position.y - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x, position.y - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);
	effect = Effect::CreateEffect(EFFECT_SPIRIT, position.x + 32, position.y - 32, -1, spriteHandler, manager);
	manager->groupEffect->AddObject(effect);

	manager->Simon->score += 3000;
	health = 0;
	isActive = false;

	// tạo item add vào world
	Item* newItem = Item::CreateItem(CRYSTAL, this->position.x, this->position.y, spriteHandler, manager);
	manager->groupItem->AddObject(newItem);
}

void Medusa::Collision()
{
	Enemy::Collision();
	Game::gameSound->playSound(HITSOFT);
}

void Medusa::CheckActive()
{
	if (position.x < Sprite::cameraXLeft || position.x > Sprite::cameraXRight)
		isActive = false;
}

void Medusa::isSimonNear() {
	if (manager->Simon->position.x <= (position.x - 150)
		&& manager->Simon->position.y >= position.y)
		isActive = false;
}
void Medusa::checkShow() {
	if (manager->Simon->position.x <= position.x - 200)
		isShown = true;
}
void Medusa::TakeDamage(int Damage)
{
	Game::gameSound->playSound(HITSOFT);
	health -= (Damage/2);
	if (health <= 0)
	{
		Destroy();
	}
	else
	{
		Effect* effect = Effect::CreateEffect(EFFECT_HIT, position.x + 14, position.y, -1, spriteHandler, manager);
		manager->groupEffect->AddObject(effect);
		position.x -= 4;
	}
}

void Medusa::createSnakes(const float &_DeltaTime) {
	timePause -= _DeltaTime;
	if (timePause < 0)
	{
		sprite->Next(2, 3);
		velocity.x = 0;
		velocity.y = 0;

		//time giữa 2 rắn
		if (timePause > -0.2)
		{

			//nếu simon bên phải boss thì thả rắn đi bên phải
			if (manager->Simon->position.x > position.x) {

				list_snakes[0]->Init(position.x, position.y, true);
				manager->groupEnemy->AddObject(list_snakes[0]);
			}
			//thả rắn về bên trái
			else
			{
				list_snakes[0]->Init(position.x, position.y, false);
				manager->groupEnemy->AddObject(list_snakes[0]);
			}
		}

		//thả rắn 2
		else {
			if (manager->Simon->position.x > position.x) {
				list_snakes[1]->Init(position.x, position.y, true);
				manager->groupEnemy->AddObject(list_snakes[1]);
			}
			else
			{
				list_snakes[1]->Init(position.x, position.y, false);
				manager->groupEnemy->AddObject(list_snakes[1]);
			}
		}
	}
}