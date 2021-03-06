#include "SmallBlood.h"
#include "../../GameComponents/Camera.h"

SmallBloodItem::SmallBloodItem()
{
	setItemType(eItem_Small_Blood);
	_animationItem = new Animation(Define::BLOOD_IS_SMALL_ITEM, 1, 4, 10, 8, 0.07f, D3DCOLOR_XRGB(6, 113, 158));
	_width = 10;
	_height = 8;
	_vy = 200.0f;
}

SmallBloodItem::~SmallBloodItem()
{
	delete _animationItem;
}

RECT SmallBloodItem::getBound()
{
	RECT bound;

	bound.left = _posX - 5;
	bound.top = _posY - 4;
	bound.right = _posX + 5;
	bound.bottom = _posY + 4;

	return bound;
}

void SmallBloodItem::update(float dt)
{
	if(_isAllowDraw)
	{
		_animationItem->update(dt);
		BaseObject::update(dt);
	}
}

void SmallBloodItem::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
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

void SmallBloodItem::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == eOject_RockMan) {
		_isDie = true;
		obj->setHP(obj->getHP() + 3);
		this->_isAllowDraw = false;
	}
}

Item_Type SmallBloodItem::getItemType()
{
	return eItem_Small_Blood;
}