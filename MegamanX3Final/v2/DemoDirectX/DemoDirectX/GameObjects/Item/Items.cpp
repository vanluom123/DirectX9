#include "Items.h"

Items::Items()
{}

Items::~Items()
{}

RECT Items::GetBound()
{
	return RECT();
}

void Items::Update(float dt)
{
}

void Items::Draw(Camera* camera, RECT rect /*= RECT()*/, GVec2 scale /*= GVec2()*/, float angle /*= 0*/, GVec2 rotationCenter /*= GVec2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{}

void Items::OnCollision(eSideCollision side)
{}

void Items::OnCollision(BaseObject *obj)
{}
