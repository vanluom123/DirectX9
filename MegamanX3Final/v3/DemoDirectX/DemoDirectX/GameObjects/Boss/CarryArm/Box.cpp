#include "Box.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"

Box::Box(bool isr)
{
	m_isR = isr;
	m_objectType = eObjectType::OBJECT_BOX;
	m_MaxHP = 6;
	m_HP = m_MaxHP;
	m_anim = new Animation("Resources/Enemies/CarryArm/box.png", 2, 1, 48, 48);
	m_animDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	m_animDie->SetPause(true);
	m_width = m_anim->GetWidth();
	m_height = m_anim->GetHeight();
	m_vx = 0;
	m_vy = 0;
}
void Box::NewEntity()
{
	if (m_isR)
	{
		m_vx = 0;
		m_vy = 300;
		m_Damage = 4;
	}
	else
	{
		m_vx = 0;
		m_vy = 0;
	}
	m_HP = m_MaxHP;
	m_isDie = false;
	m_posX = m_startx;
	m_posY = m_starty;
}

Box::~Box()
{
	delete m_anim;
	delete m_animDie;
}

void Box::Draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotateCenter, D3DCOLOR color)
{
	if (!m_isAllowDraw) return;

	if (!GameCollision::IsCollision(camera->GetBound(), GetBound()))
	{
		if (m_isR)
			NewEntity();
	}

	if (!m_animDie->GetPause())
	{
		m_animDie->Draw(m_animDie->GetPosition(), r, scale, camera->GetTrans(), angle, rotateCenter, color);

		if (m_height > 48)
		{
			int i = 24;
			while (true)
			{
				m_animDie->SetPosition(m_posX, GetBound().top + i);
				m_animDie->Draw(m_animDie->GetPosition(), r, scale, camera->GetTrans(), angle, rotateCenter, color);

				i += 48;
				if (i > m_height)
					break;
			}
		}
	}

	if (!m_isDie)
	{
		int i = 24;
		while (true)
		{
			m_anim->SetPosition(m_posX, GetBound().top + i);
			m_anim->Draw(m_anim->GetPosition(), r, scale, camera->GetTrans(), angle, rotateCenter, color);

			if (m_isR)
			{
				if (!m_animDie->GetPause())
					m_animDie->Draw(m_animDie->GetPosition(), r, scale, camera->GetTrans(), angle, rotateCenter, color);
			}

			i += 48;
			if (i > m_height)
				return;
		}
	}
}

RECT Box::GetBound()
{
	RECT bound;

	bound.left = m_posX - m_width / 2;
	bound.top = m_posY - m_height / 2;
	bound.right = bound.left + m_width;
	bound.bottom = bound.top + m_height;

	return bound;
}

void Box::Update(float dt)
{
	// Allow to draw object
	if (!m_isAllowDraw) return;

	// Animation update
	m_anim->Update(dt);

	// Animation die update
	m_animDie->Update(dt);

	// BaseObject update
	BaseObject::Update(dt);
}

void Box::OnCollision(eSideCollision side)
{
	if (m_sideY == BaseObject::SIDE_COLLISION_BOTTOM && m_isR)
	{
		m_HP = 1;
		m_isBottom = false;
		m_isDie = true;
		m_animDie->SetPosition(GetPosition());
		m_animDie->SetAnimation(0, 10, 0.05f, false);
	}
}

void Box::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() == eObjectType::OBJECT_ROCK_MAN_BULLET && !m_isDie)
	{
		m_HP -= obj->GetDamage();
		if (m_HP <= 0)
		{
			m_HP = 1;
			m_isBottom = false;
			m_isDie = true;
			m_animDie->SetPosition(GetPosition());
			m_animDie->SetAnimation(0, 8, 0.05f, false);
		}
	}
}