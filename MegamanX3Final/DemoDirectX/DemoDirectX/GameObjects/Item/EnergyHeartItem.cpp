#include "EnergyHeartItem.h"
#include "../../GameComponents/Camera.h"

EnergyHeartItem::EnergyHeartItem()
{
	SetItemsType(ENERGY);
	bigItem = new Animation("Resources/Items/energy-hearts.bmp", 1, 4, 14, 15, 0.15);
	width = 14;
	height = 14;
	vy = 200;
}

EnergyHeartItem::~EnergyHeartItem()
{
	delete bigItem;
}

RECT EnergyHeartItem::GetBound()
{
	RECT r;

	r.left = x - 7;
	r.top = y - 7;
	r.right = x + 7;
	r.bottom = y + 7;

	return r;
}

void EnergyHeartItem::Update(float dt)
{
	if (allowDraw == false)
		return;
	bigItem->update(dt);
	Entity::Update(dt);
}

void EnergyHeartItem::Draw(Camera* camera, RECT rect /*= RECT()*/, D3DXVECTOR2 scale /*= D3DXVECTOR2()*/, float angle /*= 0*/, D3DXVECTOR2 rotationCenter /*= D3DXVECTOR2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (allowDraw == false)
		return;

	bigItem->setPosition(GetPosition());
	if (camera != NULL)
		bigItem->draw(GetPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		bigItem->draw(GetPosition());
}

void EnergyHeartItem::OnCollision(Entity *obj)
{
	if (obj->GetTag() == Entity::ROCK_MAN) {
		isDie = true;
		obj->SetMaxHP(obj->GetMaxHP() + 2);
		this->allowDraw = false;
	}
}

Items::ItemsType EnergyHeartItem::GetItemsType()
{
	return ENERGY;
}
