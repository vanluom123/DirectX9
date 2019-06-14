#include "SmallSubtankItem.h"
#include "../../GameComponents/Camera.h"

SmallSubtankItem::SmallSubtankItem()
{
	setItemType(SMALL_SUBTANK);
	_animationItem = new Animation("Resources/Items/sub-tanks_small.bmp", 1, 3, 8, 8, 0.15, D3DCOLOR_XRGB(6, 113, 158));
	_width = 10;
	_height = 8;
	_vy = 200;
}

SmallSubtankItem::~SmallSubtankItem()
{
	SAFE_DELETE(_animationItem);
}

RECT SmallSubtankItem::getBound()
{
	RECT bound;

	bound.left = _posX - _width / 2;
	bound.top = _posY - _height / 2;
	bound.right = bound.left + _width;
	bound.bottom = bound.top + _height;

	return bound;
}

void SmallSubtankItem::update(float dt)
{
	if (_isAllowDraw == false)
		return;
	_animationItem->update(dt);
	BaseObject::update(dt);
}

void SmallSubtankItem::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{
	if (_isAllowDraw == false)
		return;
	_animationItem->setPosition(getPosition());
	if (camera != NULL)
		_animationItem->draw(getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		_animationItem->draw(getPosition());
}

void SmallSubtankItem::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == BaseObject::ROCK_MAN) {
		_isDie = true;
		this->_isAllowDraw = false;
	}
}

Items::eItemType SmallSubtankItem::getItemType()
{
	return SMALL_SUBTANK;
}