#include "BigBloodItem.h"
#include "../../GameComponents/Camera.h"

BigBloodItem::BigBloodItem()
{
	SetItemType(BIG_BLOOD);
	_bigItem = new Animation("Resources/Items/big_blood.bmp", 1, 4, 18, 14, 0.15);
	_width = 18;
	_height = 14;
	_vy = 200;
}

BigBloodItem::~BigBloodItem()
{
	delete _bigItem;
}

RECT BigBloodItem::GetBound()
{
	RECT bound;

	bound.left = _posX - 9;
	bound.top = _posY - 7;
	bound.right = _posX + 9;
	bound.bottom = _posY + 7;

	return bound;
}

void BigBloodItem::Update(float dt)
{
	if (_isAllowDraw == false)
		return;
	_bigItem->Update(dt);
	BaseObject::Update(dt);
}

void BigBloodItem::Draw(Camera* camera, RECT rect /*= RECT()*/, GVec2 scale /*= GVec2()*/, float angle /*= 0*/, GVec2 rotationCenter /*= GVec2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (_isAllowDraw == false)
		return;
	_bigItem->SetPosition(GetPosition());
	if (camera != NULL)
		_bigItem->Draw(GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	else
		_bigItem->Draw(GetPosition());
}

void BigBloodItem::OnCollision(BaseObject *obj)
{
	if (obj->GetObjectType() == BaseObject::ROCK_MAN) {
		_isDie = true;
		obj->SetHP(obj->GetHP() + 8);
		this->_isAllowDraw = false;
	}
}

Items::eItemType BigBloodItem::GetItemsType()
{
	return BIG_BLOOD;
}

