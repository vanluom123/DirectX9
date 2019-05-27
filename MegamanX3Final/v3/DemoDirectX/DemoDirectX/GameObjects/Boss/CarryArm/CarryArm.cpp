#include "CarryArm.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"

CarryArm::CarryArm()
{
	m_objectType = eObjectType::OBJECT_ENEMY;
	m_vx = 0;
	m_vy = 0;
	m_anim = new Animation(Define::CARRY_ARM, 3, 10, 44, 65, 0.15, D3DCOLOR_XRGB(255, 0, 220));
	m_animDie = new Animation(Define::BURST, 1, 9, 50, 45);
	m_animDie->SetPause(true);
	m_currentState = CARRY_ARM_UNKNOWN;
	SetState(CARRY_ARM_STAND);
	m_MaxHP = 5;
	m_HP = m_MaxHP;
	m_Damage = 3;
}

CarryArm::~CarryArm()
{
	delete m_anim;
	delete m_animDie;
}

void CarryArm::Draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotateCenter, D3DCOLOR color)
{
	if (!m_isAllowDraw)
		return;

	if (!m_isDie)
	{
		m_anim->SetPosition(GetPosition());
		m_anim->Draw(m_anim->GetPosition(), r, scale, camera->GetTrans(), angle, rotateCenter, color);
	}
	if (!m_animDie->GetPause())
		m_animDie->Draw(m_animDie->GetPosition(), r, scale, camera->GetTrans(), angle, rotateCenter, color);
}

RECT CarryArm::GetBound()
{
	RECT bound;

	switch (m_currentState)
	{
	case CarryArm::CARRY_ARM_EVENT_MOVE_UP_2:
		bound.left = m_posX - 43 / 2.0f;
		bound.right = 43 + bound.left;
		bound.top = m_posY - 59 / 2.0f;
		bound.bottom = 59 + bound.top;
		break;

	default:
		bound.left = m_posX - 36 / 2.0f;
		bound.right = bound.left + 36;
		bound.top = m_posY - 57 / 2.0f;
		bound.bottom = bound.top + 57;
		break;
	}
	
	return bound;
}

void CarryArm::Update(float dt)
{
	m_anim->Update(dt);
	BaseObject::Update(dt);
	m_animDie->Update(dt);
	UpdateState(dt);
}

void CarryArm::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() == eObjectType::OBJECT_ROCK_MAN_BULLET && !m_isDie)
	{
		m_HP -= obj->GetDamage();
		if (m_HP <= 0)
		{
			m_HP = m_MaxHP;
			m_isDie = true;
			m_animDie->SetPosition(GetPosition());
			m_animDie->SetAnimation(0, 10, 0.05, false);
			SetState(CARRY_ARM_STAND);
		}
	}
}

void CarryArm::SetState(eCarryArmState state)
{
	if (m_currentState == state)
		return;

	switch (state)
	{
	case CARRY_ARM_STAND:
	case CARRY_ARM_MOVE_DOWN:
	case CARRY_ARM_MOVE_UP:
		m_anim->SetAnimation(0, 10, 0.05f);
		break;

	case CARRY_ARM_EVENT_MOVE_UP:
		m_anim->SetAnimation(1, 5, 0.05f, false);
		break;

	case CARRY_ARM_EVENT_MOVE_UP_2:
		m_anim->SetAnimation(2, 5, 0.05f, false);
		break;

	default:break;
	}

	SetWidth(m_anim->GetWidth());
	SetHeight(m_anim->GetHeight());

	m_currentState = state;
}

void CarryArm::UpdateState(float dt)
{
	switch (m_currentState)
	{
	case CARRY_ARM_STAND:
		m_posX = 4880;
		m_posY = 1500;
		m_vx = 0;
		m_vy = 0;
		break;

	case CARRY_ARM_MOVE_DOWN:
		m_vx = 0;
		m_vy = 80;
		if (m_posY > m_starty)
			SetState(CARRY_ARM_EVENT_MOVE_UP_2);
		break;

	case CARRY_ARM_MOVE_UP:
		m_vx = 80;
		m_vy = -30;
		if (m_posX > m_startx)
			SetState(CARRY_ARM_STAND);
		break;

	case CARRY_ARM_EVENT_MOVE_UP:
		m_vx = 0;
		m_vy = 0;
		if (m_anim->GetPause())
			SetState(CARRY_ARM_MOVE_UP);
		break;

	case CARRY_ARM_EVENT_MOVE_UP_2:
		m_vx = 0;
		m_vy = 0;
		if (m_anim->GetPause())
			SetState(CARRY_ARM_EVENT_MOVE_UP);
		break;

	default: break;
	}
}
