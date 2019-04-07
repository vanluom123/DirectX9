#include "BigBloodItem.h"
#include "../../GameComponents/Camera.h"

BigBloodItem::BigBloodItem()
{
	SetItemsType(BIG_BLOOD);
	bigItem = new Animation("Resources/Items/big_blood.bmp", 1, 4, 18, 14, 0.15);
	width = 18;
	height = 14;
	vy = 200;
}

BigBloodItem::~BigBloodItem()
{
	delete bigItem;
}

RECT BigBloodItem::GetBound()
{
	RECT r;

	r.left = x - 9;
	r.top = y - 7;
	r.right = x + 9;
	r.bottom = y + 7;

	return r;
}

void BigBloodItem::Update(float dt)
{
	if (allowDraw == false)
		return;
	bigItem->update(dt);
	Entity::Update(dt);
}

void BigBloodItem::Draw(Camera* camera, RECT rect /*= RECT()*/, D3DXVECTOR2 scale /*= D3DXVECTOR2()*/, float angle /*= 0*/, D3DXVECTOR2 rotationCenter /*= D3DXVECTOR2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (allowDraw == false)
		return;
	bigItem->setPosition(GetPosition());
	if (camera != NULL)
		bigItem->draw(GetPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		bigItem->draw(GetPosition());
}

void BigBloodItem::OnCollision(Entity *obj)
{
	if (obj->GetTag() == Entity::ROCK_MAN) {
		isDie = true;
		obj->SetHP(obj->GetHP() + 8);
		this->allowDraw = false;
	}
}

Items::ItemsType BigBloodItem::GetItemsType()
{
	return BIG_BLOOD;
}

