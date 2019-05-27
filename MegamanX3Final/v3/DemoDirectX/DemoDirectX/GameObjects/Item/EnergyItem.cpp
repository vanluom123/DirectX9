#include "EnergyItem.h"
#include "../../GameComponents/Camera.h"

EnergyItem::EnergyItem()
{
	SetItemType(ENERGY);
	m_bigItem = new Animation("Resources/Items/energy-hearts.bmp", 1, 4, 14, 15, 0.15);
	m_width = 14;
	m_height = 14;
	m_vy = 200;
}

EnergyItem::~EnergyItem()
{
	delete m_bigItem;
}

RECT EnergyItem::GetBound()
{
	RECT bound;

	bound.left = m_posX - 7;
	bound.top = m_posY - 7;
	bound.right = m_posX + 7;
	bound.bottom = m_posY + 7;

	return bound;
}

void EnergyItem::Update(float dt)
{
	if (m_isAllowDraw == false)
		return;

	m_bigItem->Update(dt);
	BaseObject::Update(dt);
}

void EnergyItem::Draw(Camera* camera, RECT rect /*= RECT()*/, GVec2 scale /*= GVec2()*/, float angle /*= 0*/, GVec2 rotationCenter /*= GVec2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (m_isAllowDraw == false)
		return;

	m_bigItem->SetPosition(GetPosition());
	if (camera != NULL)
		m_bigItem->Draw(GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	else
		m_bigItem->Draw(GetPosition());
}

void EnergyItem::OnCollision(BaseObject *obj)
{
	if (obj->GetObjectType() == BaseObject::OBJECT_ROCK_MAN) {
		m_isDie = true;
		obj->SetMaxHP(obj->GetMaxHP() + 2);
		this->m_isAllowDraw = false;
	}
}

Items::eItemType EnergyItem::GetItemsType()
{
	return ENERGY;
}
