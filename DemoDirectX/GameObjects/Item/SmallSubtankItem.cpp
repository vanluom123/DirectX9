#include "SmallSubtankItem.h"
#include "../../GameComponents/Camera.h"

SmallSubtankItem::SmallSubtankItem()
{
	this->setItemType(Enumerator::Item_Type::SMALL_SUBTANK);
	this->_animationItem = new Animation(Define::SMALL_SUB_TANK_ITEM, 1, 3, 8, 8, 0.15f, D3DCOLOR_XRGB(6, 113, 158));
	this->_width = 10;
	this->_height = 8;
	this->_velocity.y = 200.0f;
}

SmallSubtankItem::~SmallSubtankItem()
{
	delete this->_animationItem;
}

RECT SmallSubtankItem::getBound()
{
	RECT bound;

	bound.left = _position.x - _width / 2;
	bound.top = _position.y - _height / 2;
	bound.right = bound.left + _width;
	bound.bottom = bound.top + _height;

	return bound;
}

void SmallSubtankItem::update(float dt)
{
	if(this->_isAllowDraw)
	{
		this->_animationItem->update(dt);
		BaseObject::update(dt);
	}
}

void SmallSubtankItem::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{
	if(this->_isAllowDraw)
	{
		this->_animationItem->setPosition(getPosition());
		if (camera != nullptr)
			this->_animationItem->draw(getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			this->_animationItem->draw(getPosition());
	}
}

void SmallSubtankItem::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == Enumerator::Object_Type::ROCKMAN) {
		this->_isDestroy = true;
		this->_isAllowDraw = false;
	}
}

Item_Type SmallSubtankItem::getItemType()
{
	return Enumerator::Item_Type::SMALL_SUBTANK;
}