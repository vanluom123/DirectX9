#include "SubtankItem.h"
#include "../../GameComponents/Camera.h"

SubtankItem::SubtankItem()
{
	SetItemType(SUBTANK);
	_bigItem = new Animation("Resources/Items/sub-tanks.bmp", 1, 3, 14, 14, 0.15, D3DCOLOR_XRGB(6, 113, 158));
	_width = 14;
	_height = 14;
	_vy = 200;
}

SubtankItem::~SubtankItem()
{
	delete _bigItem;
}

RECT SubtankItem::GetBound()
{
	RECT bound;

	bound.left = _posX - 7;
	bound.top = _posY - 7;
	bound.right = _posX + 7;
	bound.bottom = _posY + 7;

	return bound;
}

void SubtankItem::Update(float dt)
{
	if (_isAllowDraw == false)
		return;

	_bigItem->Update(dt);
	BaseObject::Update(dt);
}

void SubtankItem::Draw(Camera* camera, RECT rect /*= RECT()*/, GVec2 scale /*= GVec2()*/, float angle /*= 0*/, GVec2 rotationCenter /*= GVec2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (_isAllowDraw == false)
		return;

	_bigItem->SetPosition(this->GetPosition());

	if (camera != NULL)
		_bigItem->Draw(this->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	else
		_bigItem->Draw(this->GetPosition());
}

void SubtankItem::OnCollision(BaseObject *obj)
{
	if (obj->GetObjectType() == BaseObject::ROCK_MAN) {
		_isDie = true;
		this->_isAllowDraw = false;
	}
}

Items::eItemType SubtankItem::GetItemsType()
{
	return SUBTANK;
}

