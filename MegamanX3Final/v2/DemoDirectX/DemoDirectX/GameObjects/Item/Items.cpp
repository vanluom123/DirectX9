#include "Items.h"

Items::Items()
{}

Items::~Items()
{}

RECT Items::getBound()
{
	return RECT();
}

void Items::update(float dt)
{}

void Items::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{}

void Items::onCollision(eSideCollision side)
{}

void Items::onCollision(BaseObject* obj)
{}
