#include "SmallSubtank.h"
#include "../../GameComponents/Camera.h"

SmallSubtank::SmallSubtank()
{
	SetItemsType(SMALL_SUBTANKS);
	small_item = new Animation("Resources/Items/sub-tanks_small.bmp", 1, 3, 8, 8, 0.15, D3DCOLOR_XRGB(6, 113, 158));
	width = 10;
	height = 8;
	vy = 200;
}

SmallSubtank::~SmallSubtank()
{
	delete small_item;
}

RECT SmallSubtank::GetBound()
{
	RECT r;

	r.left = x - width / 2;
	r.top = y - height / 2;
	r.right = r.left + width;
	r.bottom = r.top + height;

	return r;
}

void SmallSubtank::Update(float dt)
{
	if (allowDraw == false)
		return;
	small_item->update(dt);
	Entity::Update(dt);
}

void SmallSubtank::Draw(Camera* camera, RECT rect /*= RECT()*/, D3DXVECTOR2 scale /*= D3DXVECTOR2()*/, float angle /*= 0*/, D3DXVECTOR2 rotationCenter /*= D3DXVECTOR2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (allowDraw == false)
		return;
	small_item->setPosition(GetPosition());
	if (camera != NULL)
		small_item->draw(GetPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		small_item->draw(GetPosition());
}

void SmallSubtank::OnCollision(Entity *obj)
{
	if (obj->GetTag() == Entity::ROCK_MAN) {
		isDie = true;
		this->allowDraw = false;
	}
}

Items::ItemsType SmallSubtank::GetItemsType()
{
	return SMALL_SUBTANKS;
}

