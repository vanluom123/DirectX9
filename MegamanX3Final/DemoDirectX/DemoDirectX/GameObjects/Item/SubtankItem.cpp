#include "SubtankItem.h"
#include "../../GameComponents/Camera.h"

SubtankItem::SubtankItem()
{
	SetItemsType(SUBTANKS);
	bigItem = new Animation("Resources/Items/sub-tanks.bmp", 1, 3, 14, 14, 0.15, D3DCOLOR_XRGB(6, 113, 158));
	width = 14;
	height = 14;
	vy = 200;
}

SubtankItem::~SubtankItem()
{
	delete bigItem;
}

RECT SubtankItem::GetBound()
{
	RECT r;

	r.left = x - 7;
	r.top = y - 7;
	r.right = x + 7;
	r.bottom = y + 7;

	return r;
}

void SubtankItem::Update(float dt)
{
	if (allowDraw == false)
		return;
	bigItem->update(dt);
	Entity::Update(dt);
}

void SubtankItem::Draw(Camera* camera, RECT rect /*= RECT()*/, D3DXVECTOR2 scale /*= D3DXVECTOR2()*/, float angle /*= 0*/, D3DXVECTOR2 rotationCenter /*= D3DXVECTOR2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (allowDraw == false)
		return;
	bigItem->setPosition(this->GetPosition());
	if (camera != NULL)
		bigItem->draw(this->GetPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		bigItem->draw(this->GetPosition());
}

void SubtankItem::OnCollision(Entity *obj)
{
	if (obj->GetTag() == Entity::ROCK_MAN) {
		isDie = true;
		this->allowDraw = false;
	}
}

Items::ItemsType SubtankItem::GetItemsType()
{
	return SUBTANKS;
}

