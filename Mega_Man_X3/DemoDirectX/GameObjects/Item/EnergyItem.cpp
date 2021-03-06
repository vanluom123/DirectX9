#include "EnergyItem.h"
#include "../../GameComponents/Camera.h"

EnergyItem::EnergyItem()
{
	setItemType(eItem_Enegy);
	_animationItem = new Animation(Define::ENEGY_ITEM, 1, 4, 14, 15, 0.15f);
	_width = 14;
	_height = 14;
	_vy = 200.0f;
}

EnergyItem::~EnergyItem()
{
	delete _animationItem;
}

RECT EnergyItem::getBound()
{
	RECT bound;

	bound.left = _posX - 7;
	bound.top = _posY - 7;
	bound.right = _posX + 7;
	bound.bottom = _posY + 7;

	return bound;
}

void EnergyItem::update(float dt)
{
	if (_isAllowDraw)
	{
		_animationItem->update(dt);
		BaseObject::update(dt);
	}
}

void EnergyItem::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{
	if (_isAllowDraw)
	{
		_animationItem->setPosition(getPosition());
		if (camera)
			_animationItem->draw(getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			_animationItem->draw(getPosition());
	}
}

void EnergyItem::onCollision(BaseObject *obj)
{
	if (obj->getObjectType() == eOject_RockMan) {
		_isDie = true;
		obj->setMaxHP(obj->getMaxHP() + 2);
		this->_isAllowDraw = false;
	}
}

Item_Type EnergyItem::getItemType()
{
	return eItem_Enegy;
}
