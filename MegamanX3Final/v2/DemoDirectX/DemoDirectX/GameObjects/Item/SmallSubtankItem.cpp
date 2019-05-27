#include "SmallSubtankItem.h"
#include "../../GameComponents/Camera.h"

SmallSubtankItem::SmallSubtankItem()
{
	SetItemType(SMALL_SUBTANK);
	_small_item = new Animation("Resources/Items/sub-tanks_small.bmp", 1, 3, 8, 8, 0.15, D3DCOLOR_XRGB(6, 113, 158));
	_width = 10;
	_height = 8;
	_vy = 200;
}

SmallSubtankItem::~SmallSubtankItem()
{
	SAFE_DELETE(_small_item);
}

RECT SmallSubtankItem::GetBound()
{
	RECT bound;

	bound.left = _posX - _width / 2;
	bound.top = _posY - _height / 2;
	bound.right = bound.left + _width;
	bound.bottom = bound.top + _height;

	return bound;
}

void SmallSubtankItem::Update(float dt)
{
	if (_isAllowDraw == false)
		return;
	_small_item->Update(dt);
	BaseObject::Update(dt);
}

void SmallSubtankItem::Draw(Camera* camera, RECT rect /*= RECT()*/, GVec2 scale /*= GVec2()*/, float angle /*= 0*/, GVec2 rotationCenter /*= GVec2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (_isAllowDraw == false)
		return;
	_small_item->SetPosition(GetPosition());
	if (camera != NULL)
		_small_item->Draw(GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	else
		_small_item->Draw(GetPosition());
}

void SmallSubtankItem::OnCollision(BaseObject *obj)
{
	if (obj->GetObjectType() == BaseObject::ROCK_MAN) {
		_isDie = true;
		this->_isAllowDraw = false;
	}
}

Items::eItemType SmallSubtankItem::GetItemsType()
{
	return SMALL_SUBTANK;
}

