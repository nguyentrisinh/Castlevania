#include "GameObject.h"


// --- constructor & destructor ---
GameObject::GameObject()
{
	manager = NULL;

	isActive = false;
	objectType = 0;

	sizeWidth = 0;
	sizeHeight = 0;

	sprite = NULL;
	timerSprite = 0;
	collider = NULL;

	postX = 0;
	postY = 0;
	velocityX = 0;
	velocityY = 0;
}


GameObject::~GameObject()
{
	if (collider != NULL)
	{
		delete collider;
	}
	manager = NULL;
}

// --- các hàm chính ---
// trả về vị trí (của this) va chạm, trả về vector 0 nếu không có va chạm
// cách thức: swept AABB
D3DXVECTOR3 GameObject::vecCollide(GameObject *target)
{
	D3DXVECTOR3 temp(0, 0, 0);

	if ((target->collider == NULL) || (this->collider == NULL))
		return temp;

	// swept AABB here

	return temp;
}

// có va chạm hay không
// cách thức: có lồng vào nhau hay không
bool GameObject::isCollide(GameObject *target)
{
	// cả 2 phải có collider mới va chạm được
	if ((target->collider == NULL) || (this->collider == NULL))
		return false;
	
	// cạnh trái của this > cạnh phải của target
	if ((postX + collider->left) > (target->postX + target->collider->right))
		return false;

	// cạnh phải của this < cạnh trái của target
	if ((postX + collider->right) < (target->postX + target->collider->left))
		return false;

	// cạnh trên của this < cạnh dưới của target
	if ((postY + collider->top) < (target->postY + target->collider->bottom))
		return false;

	// cạnh dưới của this > cạnh trên của target
	if ((postY + collider->bottom) > (target->postY + target->collider->top))
		return false;

	// ko thoả điều kiện nào hết => đang nằm lồng vào nhau
	return true;
}


// --- cac phuong thuc ao
void GameObject::Init(int _X, int _Y) {}
void GameObject::Update(const float &_DeltaTime) {}
void GameObject::Render() {}
void GameObject::Destroy() {}
void GameObject::Collision() {};

