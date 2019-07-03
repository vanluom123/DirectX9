#include "Item.h"

Item::Item()
{
	_itemsType = eItem_None;
	_animationItem = nullptr;
}

Item::~Item()
{}

RECT Item::getBound()
{
	return RECT();
}

void Item::update(float dt)
{}

void Item::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{}

void Item::onCollision(Side_Collision side)
{}

void Item::onCollision(BaseObject* obj)
{}

void Item::setItemType(Item_Type val) { _itemsType = val; }
