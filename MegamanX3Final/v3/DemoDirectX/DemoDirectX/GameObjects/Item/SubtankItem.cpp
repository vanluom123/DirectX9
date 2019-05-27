#include "SubtankItem.h"
#include "../../GameComponents/Camera.h"

SubtankItem::SubtankItem()
{
	SetItemType(SUBTANK);
	m_bigItem = new Animation("Resources/Items/sub-tanks.bmp", 1, 3, 14, 14, 0.15, D3DCOLOR_XRGB(6, 113, 158));
	m_width = 14;
	m_height = 14;
	m_vy = 200;
}

SubtankItem::~SubtankItem()
{
	delete m_bigItem;
}

RECT SubtankItem::GetBound()
{
	RECT bound;

	bound.left = m_posX - 7;
	bound.top = m_posY - 7;
	bound.right = m_posX + 7;
	bound.bottom = m_posY + 7;

	return bound;
}

void SubtankItem::Update(float dt)
{
	if (m_isAllowDraw == false)
		return;

	m_bigItem->Update(dt);
	BaseObject::Update(dt);
}

void SubtankItem::Draw(Camera* camera, RECT rect /*= RECT()*/, GVec2 scale /*= GVec2()*/, float angle /*= 0*/, GVec2 rotationCenter /*= GVec2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (m_isAllowDraw == false)
		return;

	m_bigItem->SetPosition(this->GetPosition());

	if (camera != NULL)
		m_bigItem->Draw(this->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	else
		m_bigItem->Draw(this->GetPosition());
}

void SubtankItem::OnCollision(BaseObject *obj)
{
	if (obj->GetObjectType() == BaseObject::OBJECT_ROCK_MAN) {
		m_isDie = true;
		this->m_isAllowDraw = false;
	}
}

Items::eItemType SubtankItem::GetItemsType()
{
	return SUBTANK;
}

