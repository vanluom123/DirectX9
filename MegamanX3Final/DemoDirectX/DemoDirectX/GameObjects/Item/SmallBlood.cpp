#include "SmallBlood.h"
#include "../../GameComponents/Camera.h"

SmallBloodItem::SmallBloodItem()
{
	SetItemsType(SMALL_BLOOD);
	small_item = new Animation("Resources/Items/small_blood.bmp", 1, 4, 10, 8, 0.07, D3DCOLOR_XRGB(6, 113, 158));
	width = 10;
	height = 8;
	vy = 200;
}

SmallBloodItem::~SmallBloodItem()
{
	delete small_item;
}

RECT SmallBloodItem::GetBound()
{
	RECT r;

	r.left = x - 5;
	r.top = y - 4;
	r.right = x + 5;
	r.bottom = y + 4;

	return r;
}

void SmallBloodItem::Update(float dt)
{
	if (allowDraw == false)
		return;
	small_item->update(dt);
	Entity::Update(dt);
}

void SmallBloodItem::Draw(Camera* camera, RECT rect /*= RECT()*/, D3DXVECTOR2 scale /*= D3DXVECTOR2()*/, float angle /*= 0*/, D3DXVECTOR2 rotationCenter /*= D3DXVECTOR2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (allowDraw == false)
		return;
	small_item->setPosition(GetPosition());
	if (camera != NULL)
		small_item->draw(GetPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		small_item->draw(GetPosition());
}

void SmallBloodItem::OnCollision(Entity *obj)
{
	if (obj->GetTag() == Entity::ROCK_MAN) {
		isDie = true;
		obj->SetHP(obj->GetHP() + 3);
		this->allowDraw = false;
	}
}

Items::ItemsType SmallBloodItem::GetItemsType()
{
	return SMALL_BLOOD;
}

