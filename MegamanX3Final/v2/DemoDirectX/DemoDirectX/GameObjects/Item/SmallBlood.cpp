#include "SmallBlood.h"
#include "../../GameComponents/Camera.h"

SmallBloodItem::SmallBloodItem()
{
	SetItemType(SMALL_BLOOD);
	_small_item = new Animation("Resources/Items/small_blood.bmp", 1, 4, 10, 8, 0.07, D3DCOLOR_XRGB(6, 113, 158));
	_width = 10;
	_height = 8;
	_vy = 200;
}

SmallBloodItem::~SmallBloodItem()
{
	delete _small_item;
}

RECT SmallBloodItem::GetBound()
{
	RECT bound;

	bound.left = _posX - 5;
	bound.top = _posY - 4;
	bound.right = _posX + 5;
	bound.bottom = _posY + 4;

	return bound;
}

void SmallBloodItem::Update(float dt)
{
	if (_isAllowDraw == false)
		return;
	_small_item->Update(dt);
	BaseObject::Update(dt);
}

void SmallBloodItem::Draw(Camera* camera, RECT rect /*= RECT()*/, GVec2 scale /*= GVec2()*/, float angle /*= 0*/, GVec2 rotationCenter /*= GVec2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (_isAllowDraw == false)
		return;
	_small_item->SetPosition(GetPosition());
	if (camera != NULL)
		_small_item->Draw(GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	else
		_small_item->Draw(GetPosition());
}

void SmallBloodItem::OnCollision(BaseObject *obj)
{
	if (obj->GetObjectType() == BaseObject::ROCK_MAN) {
		_isDie = true;
		obj->SetHP(obj->GetHP() + 3);
		this->_isAllowDraw = false;
	}
}

Items::eItemType SmallBloodItem::GetItemsType()
{
	return SMALL_BLOOD;
}

