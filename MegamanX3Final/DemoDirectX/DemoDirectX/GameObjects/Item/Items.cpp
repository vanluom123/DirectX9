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

void Items::Draw(Camera* camera, RECT rect /*= RECT()*/, D3DXVECTOR2 scale /*= D3DXVECTOR2()*/, float angle /*= 0*/, D3DXVECTOR2 rotationCenter /*= D3DXVECTOR2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{}

void Items::OnCollision(SideCollisions side)
{}

void Items::OnCollision(Entity *obj)
{}
