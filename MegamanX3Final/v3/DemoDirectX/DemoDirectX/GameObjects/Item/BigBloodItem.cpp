#include "BigBloodItem.h"
#include "../../GameComponents/Camera.h"

BigBloodItem::BigBloodItem()
{
	SetItemType(BIG_BLOOD);
	m_bigItem = new Animation("Resources/Items/big_blood.bmp", 1, 4, 18, 14, 0.15);
	m_width = 18;
	m_height = 14;
	m_vy = 200;
}

BigBloodItem::~BigBloodItem()
{
	delete m_bigItem;
}

RECT BigBloodItem::GetBound()
{
	RECT bound;

	bound.left = m_posX - 9;
	bound.top = m_posY - 7;
	bound.right = m_posX + 9;
	bound.bottom = m_posY + 7;

	return bound;
}

void BigBloodItem::Update(float dt)
{
	if (m_isAllowDraw == false)
		return;
	m_bigItem->Update(dt);
	BaseObject::Update(dt);
}

void BigBloodItem::Draw(Camera* camera, RECT rect /*= RECT()*/, GVec2 scale /*= GVec2()*/, float angle /*= 0*/, GVec2 rotationCenter /*= GVec2()*/, D3DCOLOR color /*= D3DCOLOR_XRGB(255, 255, 255)*/)
{
	if (m_isAllowDraw == false)
		return;
	m_bigItem->SetPosition(GetPosition());
	if (camera != NULL)
		m_bigItem->Draw(GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	else
		m_bigItem->Draw(GetPosition());
}

void BigBloodItem::OnCollision(BaseObject *obj)
{
	if (obj->GetObjectType() == BaseObject::OBJECT_ROCK_MAN) {
		m_isDie = true;
		obj->SetHP(obj->GetHP() + 8);
		this->m_isAllowDraw = false;
	}
}

Items::eItemType BigBloodItem::GetItemsType()
{
	return BIG_BLOOD;
}

