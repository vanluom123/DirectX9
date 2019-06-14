#include "EnergyItem.h"
#include "../../GameComponents/Camera.h"

EnergyItem::EnergyItem()
{
	setItemType(ENERGY);
	_animationItem = new Animation("Resources/Items/energy-hearts.bmp", 1, 4, 14, 15, 0.15);
	_width = 14;
	_height = 14;
	_vy = 200;
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
	if (_isAllowDraw == false)
		return;
	_animationItem->update(dt);
	BaseObject::update(dt);
}

void EnergyItem::draw(Camera* camera, RECT rect /*= RECT()*/, GVec2 scale /*= GVec2()*/, float angle /*= 0*/, GVec2 rotationCenter /*= GVec2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (_isAllowDraw == false)
		return;

	_animationItem->setPosition(getPosition());
	if (camera != NULL)
		_animationItem->draw(getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		_animationItem->draw(getPosition());
}

void EnergyItem::onCollision(BaseObject *obj)
{
	if (obj->getObjectType() == BaseObject::ROCK_MAN) {
		_isDie = true;
		obj->setMaxHP(obj->getMaxHP() + 2);
		this->_isAllowDraw = false;
	}
}

Items::eItemType EnergyItem::getItemType()
{
	return ENERGY;
}
