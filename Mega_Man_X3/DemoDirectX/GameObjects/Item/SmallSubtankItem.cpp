#include "SmallSubtankItem.h"
#include "../../GameComponents/Camera.h"

SmallSubtankItem::SmallSubtankItem()
{
	setItemType(eItem_Small_Subtank);
	_animationItem = new Animation(Define::SMALL_SUB_TANK_ITEM, 1, 3, 8, 8, 0.15f, D3DCOLOR_XRGB(6, 113, 158));
	_width = 10;
	_height = 8;
	_vy = 200.0f;
}

SmallSubtankItem::~SmallSubtankItem()
{
	delete _animationItem;
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
	if(_isAllowDraw)
	{
		_animationItem->update(dt);
		BaseObject::update(dt);
	}
}

void SmallSubtankItem::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{
	if(_isAllowDraw)
	{
		_animationItem->setPosition(getPosition());
		if (camera != NULL)
			_animationItem->draw(getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			_animationItem->draw(getPosition());
	}
}

void SmallSubtankItem::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == eOject_RockMan) {
		_isDie = true;
		this->_isAllowDraw = false;
	}
}

Item_Type SmallSubtankItem::getItemType()
{
	return eItem_Small_Subtank;
}