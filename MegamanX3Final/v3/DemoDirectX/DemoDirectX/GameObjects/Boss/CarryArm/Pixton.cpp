#include "Pixton.h"
#include "../../../GameComponents/Camera.h"


Pixton::Pixton()
{
	m_isBottom = false;
	m_anim = new Animation("Resources/Enemies/CarryArm/x3_subboss_carryarm_39.png", 1, 1, 144, 88);
	this->SetWidth(m_anim->GetWidth());
	this->SetHeight(m_anim->GetHeight());
	m_pixtonPosY = 0;
}

Pixton::~Pixton()
{
	delete m_anim;
}

RECT Pixton::GetBound()
{
	RECT bound;
	bound.left = m_posX - m_width / 2;
	bound.right = m_posX + m_width / 2;
	bound.bottom = m_posY + m_height / 2;
	bound.top = bound.bottom -16;
	return bound;
}

void Pixton::Draw(Camera * camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	if (!m_isAllowDraw)
		return;

	m_anim->SetPosition(GetPosition());
	if (camera)
		m_anim->Draw(m_anim->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);
	else
		m_anim->Draw(m_anim->GetPosition());
}

void Pixton::OnCollision(eSideCollision side)
{
}

void Pixton::Update(float gameTime)
{
	if (!m_isAllowDraw)
		return;

	m_anim->Update(gameTime);
	BaseObject::Update(gameTime);
}

bool Pixton::MoveDown(float gameTime, float x, float y)
{
	if (!m_isBottom)
	{
		m_pixtonPosY += 40 * gameTime;
		if (m_pixtonPosY >= 88)
		{
			m_isBottom = true;
			m_pixtonPosY = 88;
		}
		SetPosition(x + 55, y + m_pixtonPosY);
	}
	return !m_isBottom;
}

bool Pixton::MoveUp(float gameTime, float x, float y)
{
	if (m_isBottom)
	{
		m_pixtonPosY -= 40 * gameTime;
		if (m_pixtonPosY <= 0)
		{
			m_isBottom = false;
			m_pixtonPosY = 0;
			m_vy = -40;
		}
		SetPosition(x + 56, y + m_pixtonPosY);
	}
	return m_isBottom;
}
