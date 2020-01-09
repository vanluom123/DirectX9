#include "SmallBlood.h"
#include "../../GameComponents/Camera.h"

SmallBloodItem::SmallBloodItem()
{
	this->setItemType(Enumerator::Item_Type::SMALL_BLOOD);
	this->_animationItem = new Animation(Define::BLOOD_IS_SMALL_ITEM, 1, 4, 10, 8, 0.07f, D3DCOLOR_XRGB(6, 113, 158));
	this->_width = 10;
	this->_height = 8;
	this->_vy = 200.0f;
}

SmallBloodItem::~SmallBloodItem()
{
	delete this->_animationItem;
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
	if(this->_isAllowDraw)
	{
		this->_animationItem->update(dt);
		BaseObject::update(dt);
	}
}

void SmallBloodItem::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{
	if(this->_isAllowDraw)
	{
		this->_animationItem->setPosition(getPosition());
		if (camera != NULL)
			this->_animationItem->draw(getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			this->_animationItem->draw(getPosition());
	}
}

void SmallBloodItem::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == Enumerator::Object_Type::ROCKMAN) {
		this->_isDestroy = true;
		obj->setHP(obj->getHP() + 3);
		this->_isAllowDraw = false;
	}
}

Item_Type SmallBloodItem::getItemType()
{
	return Enumerator::Item_Type::SMALL_BLOOD;
}