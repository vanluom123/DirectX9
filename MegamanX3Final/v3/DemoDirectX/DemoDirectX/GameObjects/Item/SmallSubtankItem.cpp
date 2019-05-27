#include "SmallSubtankItem.h"
#include "../../GameComponents/Camera.h"

SmallSubtankItem::SmallSubtankItem()
{
	SetItemType(SMALL_SUBTANK);
	m_small_item = new Animation("Resources/Items/sub-tanks_small.bmp", 1, 3, 8, 8, 0.15, D3DCOLOR_XRGB(6, 113, 158));
	m_width = 10;
	m_height = 8;
	m_vy = 200;
}

SmallSubtankItem::~SmallSubtankItem()
{
	SAFE_DELETE(m_small_item);
}

RECT SmallSubtankItem::GetBound()
{
	RECT bound;

	bound.left = m_posX - m_width / 2;
	bound.top = m_posY - m_height / 2;
	bound.right = bound.left + m_width;
	bound.bottom = bound.top + m_height;

	return bound;
}

void SmallSubtankItem::Update(float dt)
{
	if (m_isAllowDraw == false)
		return;
	m_small_item->Update(dt);
	BaseObject::Update(dt);
}

void SmallSubtankItem::Draw(Camera* camera, RECT rect /*= RECT()*/, GVec2 scale /*= GVec2()*/, float angle /*= 0*/, GVec2 rotationCenter /*= GVec2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (m_isAllowDraw == false)
		return;
	m_small_item->SetPosition(GetPosition());
	if (camera != NULL)
		m_small_item->Draw(GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	else
		m_small_item->Draw(GetPosition());
}

void SmallSubtankItem::OnCollision(BaseObject *obj)
{
	if (obj->GetObjectType() == BaseObject::OBJECT_ROCK_MAN) {
		m_isDie = true;
		this->m_isAllowDraw = false;
	}
}

Items::eItemType SmallSubtankItem::GetItemsType()
{
	return SMALL_SUBTANK;
}

