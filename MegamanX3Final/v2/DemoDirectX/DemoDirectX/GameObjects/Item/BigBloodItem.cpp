#include "BigBloodItem.h"
#include "../../GameComponents/Camera.h"

BigBloodItem::BigBloodItem()
{
	setItemType(eItem_Big_Blood);
	_animationItem = new Animation(Define::BLOOD_IS_BIG_ITEM, 1, 4, 18, 14, 0.15f);
	_width = 18;
	_height = 14;
	_vy = 200.0f;
}

BigBloodItem::~BigBloodItem()
{
	delete _animationItem;
}

RECT BigBloodItem::getBound()
{
	RECT bound;

	bound.left = _posX - 9;
	bound.top = _posY - 7;
	bound.right = _posX + 9;
	bound.bottom = _posY + 7;

	return bound;
}

void BigBloodItem::update(float dt)
{
	if(_isAllowDraw)
	{
		_animationItem->update(dt);
		BaseObject::update(dt);
	}
}

void BigBloodItem::draw(Camera* camera, RECT rect /*= RECT()*/, GVec2 scale /*= GVec2()*/, float angle /*= 0*/, GVec2 rotationCenter /*= GVec2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
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

void BigBloodItem::onCollision(BaseObject *obj)
{
	if (obj->getObjectType() == eOject_RockMan) {
		_isDie = true;
		obj->setHP(obj->getHP() + 8);
		this->_isAllowDraw = false;
	}
}

Item_Type BigBloodItem::getItemType()
{
	return eItem_Big_Blood;
}

