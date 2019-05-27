#include "SmallBlood.h"
#include "../../GameComponents/Camera.h"

SmallBloodItem::SmallBloodItem()
{
	SetItemType(SMALL_BLOOD);
	m_small_item = new Animation("Resources/Items/small_blood.bmp", 1, 4, 10, 8, 0.07, D3DCOLOR_XRGB(6, 113, 158));
	m_width = 10;
	m_height = 8;
	m_vy = 200;
}

SmallBloodItem::~SmallBloodItem()
{
	delete m_small_item;
}

RECT SmallBloodItem::GetBound()
{
	RECT bound;

	bound.left = m_posX - 5;
	bound.top = m_posY - 4;
	bound.right = m_posX + 5;
	bound.bottom = m_posY + 4;

	return bound;
}

void SmallBloodItem::Update(float dt)
{
	if (m_isAllowDraw == false)
		return;

	m_small_item->Update(dt);
	BaseObject::Update(dt);
}

void SmallBloodItem::Draw(Camera* camera, RECT rect /*= RECT()*/, GVec2 scale /*= GVec2()*/, float angle /*= 0*/, GVec2 rotationCenter /*= GVec2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (m_isAllowDraw == false)
		return;
	m_small_item->SetPosition(GetPosition());
	if (camera != NULL)
		m_small_item->Draw(GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	else
		m_small_item->Draw(GetPosition());
}

void SmallBloodItem::OnCollision(BaseObject *obj)
{
	if (obj->GetObjectType() == BaseObject::OBJECT_ROCK_MAN) {
		m_isDie = true;
		obj->SetHP(obj->GetHP() + 3);
		this->m_isAllowDraw = false;
	}
}

Items::eItemType SmallBloodItem::GetItemsType()
{
	return SMALL_BLOOD;
}

