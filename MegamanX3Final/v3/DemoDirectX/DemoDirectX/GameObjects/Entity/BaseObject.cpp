#include "BaseObject.h"

BaseObject::BaseObject()
{
	m_objectType = OBJECT_UNKNOWN;
	m_vx = 0;
	m_vy = 0;
	m_collisionTimeMinX = 1.0f;
	m_collisionTimeMinY = 1.0f;
	m_sideX = SIDE_COLLISION_NONE;
	m_sideY = SIDE_COLLISION_NONE;
	m_isAllowDraw = true;
	m_isDie = false;
	m_HP = 0;
	m_Damage = 0;
}

RECT BaseObject::GetBound()
{
	RECT bound;

	bound.left = m_posX - m_width / 2.0f;
	bound.right = m_posX + m_width / 2.0f;
	bound.top = m_posY - m_height / 2.0f;
	bound.bottom = m_posY + m_height / 2.0f;

	return bound;
}

void BaseObject::OnCollision(eSideCollision side)
{
	m_vx = 0, m_vy = 0;
}

void BaseObject::OnCollision(BaseObject* obj)
{}

void BaseObject::OnNoCollisionWithBottom()
{}

std::vector<BaseObject*>* BaseObject::GetListBullet()
{
	return &m_listBullet;
}

void BaseObject::SetId(int id)
{
	m_id = id;
}

int BaseObject::GetId() const
{
	return m_id;
}

void BaseObject::Update(float dt)
{
	if (m_HP > m_MaxHP)
		m_HP = m_MaxHP;

	if (m_sideX != SIDE_COLLISION_NONE)
	{
		if (m_collisionTimeMinY == 0.0f)
		{
			if (GetBound().bottom <= m_entityX->GetBound().top || GetBound().top >= m_entityX->GetBound().bottom)
			{
				m_collisionTimeMinX = 1.0f;
				m_sideX = SIDE_COLLISION_NONE;
			}
		}
		OnCollision(m_sideX);
	}
	if (m_sideY != SIDE_COLLISION_NONE)
	{
		if (m_collisionTimeMinX == 0.0f)
		{
			if (GetBound().right <= m_entityY->GetBound().left || GetBound().left >= m_entityY->GetBound().right)
			{
				m_collisionTimeMinY = 1.0f;
				m_sideY = SIDE_COLLISION_NONE;
			}
		}
		OnCollision(m_sideY);
	}
	m_posX += m_vx * dt * m_collisionTimeMinX;
	m_collisionTimeMinX = 1.0f;
	m_sideX = SIDE_COLLISION_NONE;

	m_posY += m_vy * dt * m_collisionTimeMinY;
	m_collisionTimeMinY = 1.0f;
	m_sideY = SIDE_COLLISION_NONE;
}

void BaseObject::CheckTimeCollision(float collisionTime, eSideCollision side, BaseObject* other)
{
	switch (side)
	{
	case SIDE_COLLISION_LEFT:
	case SIDE_COLLISION_RIGHT:
		if (collisionTime >= m_collisionTimeMinX)
			return;
		m_collisionTimeMinX = collisionTime;
		m_sideX = side;
		m_entityX = other;
		break;


	case SIDE_COLLISION_TOP:
	case SIDE_COLLISION_BOTTOM:
		if (collisionTime >= m_collisionTimeMinY)
			return;
		m_collisionTimeMinY = collisionTime;
		m_sideY = side;
		m_entityY = other;
		break;


	default: break;
	}
}