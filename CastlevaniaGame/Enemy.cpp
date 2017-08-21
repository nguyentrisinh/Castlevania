#include "Enemy.h"
#include "World.h"
Enemy::Enemy()
{
}

Enemy::Enemy(LPD3DXSPRITE _SpriteHandler, World *_manager)
{
	objectType = ENEMY_TYPE;
	manager = _manager;
	collider = new Collider();
	
	isActive = false;
	isDamage = false;
	sizeWidth = 64;
	sizeHeight = 64;
	spriteHandler = _SpriteHandler;
	spriteLeft = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_left.bmp", sizeWidth, sizeHeight, 29, 6);
	spriteRight = new Sprite(_SpriteHandler, "Resources\\Sprites\\creep_right.bmp", sizeWidth, sizeHeight, 29, 6);
	sprite = spriteLeft;


}

Enemy :: ~Enemy()
{

}

void Enemy::Init(int _X, int _Y)
{
}

void Enemy::Init(int _X, int _Y, bool _IsRight)
{
}

void Enemy::Update(const float &_DeltaTime)
{
}


void Enemy::Render()
{
}

void Enemy::Destroy()
{
	isActive = false;
}

void Enemy::TakeDamage(int Damage)
{
	
	
	//health -= Damage;

	// Test for Damage
	//if (!this->isDamage)
	health -= Damage;
	if (health <= 0) 
	{
		Destroy();
	}
	else 
	{
		Effect* effect = Effect::CreateEffect(EFFECT_HIT, position.x + 14, position.y, -1, spriteHandler, manager);
		manager->groupEffect->AddObject(effect);
	}
	

	
		
}

void Enemy::Collision()
{
	//Effect* effect = Effect::CreateEffect(EFFECT_HIT, position.x, position.y, -1, spriteHandler, manager);
	//manager->groupEffect->AddObject(effect);
	TakeDamage(NULL, 1);
}



void Enemy::CheckActive()
{

}

void Enemy::TakeDamage(GameObject * actor, int damage)
{
	// Test for Damage
	if (!this->isDamage)
		health -= damage;
	
	if (health <= 0)
		Destroy();
}

Enemy * Enemy::CreateEnemy(int enemyType, int X, int Y, LPD3DXSPRITE _SpriteHandler, World * _manager)
{
	Enemy* enemy = new Enemy();
	switch (enemyType)
	{
	case KNIGHT:
		enemy = new Knight(_SpriteHandler, _manager);
		enemy->Init(X, Y);
		break;
	}
	return enemy;
}

bool Enemy::CheckGroundCollision(World * manager, const float _DeltaTime)
{
	float collisionScale = 0;
	GameObject* tempObject;
	// Xét va chạm với nhóm đối tượng trong quadtree. Ví dụ như Ground, Destructibe, Zone,...
	for (int i = 0; i < (manager->groupQuadtreeCollision->number); i++)
	{
		tempObject = manager->groupQuadtreeCollision->objects[i];
		if (tempObject->objectType == GROUND_TYPE)
		{
			collisionScale = SweptAABB(tempObject, _DeltaTime);
			// nếu có va chạm
			if (collisionScale < 1.0f && normaly > 0.1f)
			{
				SlideFromGround(tempObject, _DeltaTime, collisionScale);
				return true;
			}
		}
	}
	return false;
}

Enemy* Enemy::CreateEnemy(int* parameters, LPD3DXSPRITE spriteHandler, World *manager)
{
	Enemy* newEnemy = NULL;

	switch (parameters[1] % 100)
	{
		// map1 enemies
	case REDBAT:
		newEnemy = new RedBat(spriteHandler, manager);
		break;
	case GHOUL:
		newEnemy = new Ghoul(spriteHandler, manager);
		break;
	case FISH:
		newEnemy = new Fish(spriteHandler, manager);
		break;
	case PANTHER:
		newEnemy = new Panther(spriteHandler, manager);
		break;

		// boss enemies
	case VAMBAT:
		newEnemy = new VamBat(spriteHandler, manager);
		manager->boss = newEnemy;
		break;
	case MEDUSA:
		newEnemy = new Medusa(spriteHandler, manager);
		manager->boss = newEnemy;
		break;

		// map2 enemies
	case BLUEBAT:
		newEnemy = new BlueBat(spriteHandler, manager);
		break;
	case KNIGHT:
		newEnemy = new Knight(spriteHandler, manager);
		break;
	case BONE:
		newEnemy = new Bone(spriteHandler, manager);
		break;
		/*
		case HEAD:
		newEnemy = new Head(spriteHandler, manager);
		break;
		case GHOST:
		newEnemy = new Ghost(spriteHandler, manager);
		break;
		case BONE:
		newEnemy = new Bone(spriteHandler, manager);
		break;*/
	default:
		return NULL;
		break;

	}

	// nếu vị trí == 0 thì enemy sẽ không active
	if ((parameters[2] == 0) && (parameters[3] == 0))
	{
		newEnemy->isActive = false;
	}
	else
	{
		newEnemy->Init(parameters[2], parameters[3]);
	}

	// ----------------- test 
	if (newEnemy->enemyType == VAMBAT)
		newEnemy->isActive = true;
	if (newEnemy->enemyType == MEDUSA)
		newEnemy->isActive = true;
	// --------------------

	return newEnemy;
}