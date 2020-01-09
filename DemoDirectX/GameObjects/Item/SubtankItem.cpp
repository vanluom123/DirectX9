#include "SubtankItem.h"
#include "../../GameComponents/Camera.h"

SubtankItem::SubtankItem()
{
	this->setItemType(Enumerator::Item_Type::SUBTANK);
	this->_animationItem = new Animation(Define::SUB_TANK_ITEM, 1, 3, 14, 14, 0.15f, D3DCOLOR_XRGB(6, 113, 158));
	this->_width = 14;
	this->_height = 14;
	this->_vy = 200;
}

SubtankItem::~SubtankItem()
{
	delete this->_animationItem;
}

RECT SubtankItem::getBound()
{
	RECT bound;

	bound.left = _posX - 7;
	bound.top = _posY - 7;
	bound.right = _posX + 7;
	bound.bottom = _posY + 7;

	return bound;
}

void SubtankItem::update(float dt)
{
	if(this->_isAllowDraw)
	{
		this->_animationItem->update(dt);
		BaseObject::update(dt);
	}
}

void SubtankItem::draw(Camera* camera, RECT rect /*= RECT()*/, GVec2 scale /*= GVec2()*/, float angle /*= 0*/, GVec2 rotationCenter /*= GVec2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if(this->_isAllowDraw)
	{
		this->_animationItem->setPosition(this->getPosition());

		if (camera != NULL)
			this->_animationItem->draw(this->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			this->_animationItem->draw(this->getPosition());
	}
}

void SubtankItem::onCollision(BaseObject *obj)
{
	if (obj->getObjectType() == Enumerator::Object_Type::ROCKMAN) {
		this->_isDestroy = true;
		this->_isAllowDraw = false;
	}
}

Item_Type SubtankItem::getItemType()
{
	return Enumerator::Item_Type::SUBTANK;
}

