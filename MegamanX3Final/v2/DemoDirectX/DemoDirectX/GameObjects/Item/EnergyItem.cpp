#include "EnergyItem.h"
#include "../../GameComponents/Camera.h"

EnergyItem::EnergyItem()
{
	SetItemType(ENERGY);
	_bigItem = new Animation("Resources/Items/energy-hearts.bmp", 1, 4, 14, 15, 0.15);
	_width = 14;
	_height = 14;
	_vy = 200;
}

EnergyItem::~EnergyItem()
{
	delete _bigItem;
}

RECT EnergyItem::GetBound()
{
	RECT bound;

	bound.left = _posX - 7;
	bound.top = _posY - 7;
	bound.right = _posX + 7;
	bound.bottom = _posY + 7;

	return bound;
}

void EnergyItem::Update(float dt)
{
	if (_isAllowDraw == false)
		return;
	_bigItem->Update(dt);
	BaseObject::Update(dt);
}

void EnergyItem::Draw(Camera* camera, RECT rect /*= RECT()*/, GVec2 scale /*= GVec2()*/, float angle /*= 0*/, GVec2 rotationCenter /*= GVec2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (_isAllowDraw == false)
		return;

	_bigItem->SetPosition(GetPosition());
	if (camera != NULL)
		_bigItem->Draw(GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	else
		_bigItem->Draw(GetPosition());
}

void EnergyItem::OnCollision(BaseObject *obj)
{
	if (obj->GetObjectType() == BaseObject::ROCK_MAN) {
		_isDie = true;
		obj->SetMaxHP(obj->GetMaxHP() + 2);
		this->_isAllowDraw = false;
	}
}

Items::eItemType EnergyItem::GetItemsType()
{
	return ENERGY;
}
