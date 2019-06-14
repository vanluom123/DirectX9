#include "SubtankItem.h"
#include "../../GameComponents/Camera.h"

SubtankItem::SubtankItem()
{
	setItemType(SUBTANK);
	_animationItem = new Animation("Resources/Items/sub-tanks.bmp", 1, 3, 14, 14, 0.15, D3DCOLOR_XRGB(6, 113, 158));
	_width = 14;
	_height = 14;
	_vy = 200;
}

SubtankItem::~SubtankItem()
{
	delete _animationItem;
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
	if (_isAllowDraw == false)
		return;

	_animationItem->update(dt);
	BaseObject::update(dt);
}

void SubtankItem::draw(Camera* camera, RECT rect /*= RECT()*/, GVec2 scale /*= GVec2()*/, float angle /*= 0*/, GVec2 rotationCenter /*= GVec2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (_isAllowDraw == false)
		return;

	_animationItem->setPosition(this->getPosition());

	if (camera != NULL)
		_animationItem->draw(this->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		_animationItem->draw(this->getPosition());
}

void SubtankItem::onCollision(BaseObject *obj)
{
	if (obj->getObjectType() == BaseObject::ROCK_MAN) {
		_isDie = true;
		this->_isAllowDraw = false;
	}
}

Items::eItemType SubtankItem::getItemType()
{
	return SUBTANK;
}

