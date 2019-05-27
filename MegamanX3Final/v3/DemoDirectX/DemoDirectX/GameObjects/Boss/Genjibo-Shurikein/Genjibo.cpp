#include "Genjibo.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/BigBloodItem.h"

Genjibo::Genjibo()
{
	m_objectType = eObjectType::OBJECT_BOSS;
	m_isAllowDraw = false;
	m_timeStand = 0;
	m_timeMove = 0;
	m_posY = m_posY;
	m_transY = 15;
	m_count = 0;
	m_MaxHP = 30;
	m_HP = m_MaxHP;
	m_Damage = 4;
	m_anim = new Animation(Define::GENJIBO_SHURIKEIN, 8, 17, 49, 49, 0.01f);
	m_animGenjinbo = new Animation(Define::SHURIKEN, 2, 2, 32, 68, 0.01f);
	m_animDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.05);
	m_sideGen = SIDE_COLLISION_NONE;
	m_change = false;
	m_shurikeinState = SHURIKEIN_STAND;
	SetState(SHURIKEIN_APPEAR);
}


Genjibo::~Genjibo()
{
	delete m_anim;
	delete m_animGenjinbo;
	delete m_animDie;
}

RECT Genjibo::GetBound()
{
	RECT bound;
	bound.left = m_posX - m_width / 2.0f;
	bound.right = bound.left + m_width;
	bound.top = m_posY - m_height / 2.0f;
	bound.bottom = bound.top + m_height;
	return bound;
}

void Genjibo::Update(float dt)
{
	for (auto& bullet : m_listBullet)
		bullet->Update(dt);

	if (m_isDie == true)
	{
		if (m_animDie->GetPause() == true)
			return;
		m_animDie->Update(dt);
	}
	else
		m_anim->Update(dt);

	m_animGenjinbo->Update(dt);
	UpdateState(dt);
	BaseObject::Update(dt);
}

void Genjibo::OnCollision(BaseObject * obj)
{
	if (obj->GetObjectType() == eObjectType::OBJECT_ROCK_MAN_BULLET)
	{
		m_HP -= 2;
		if (m_HP < 0)
		{
			m_isDie = true;
			SetState(SHURIKEIN_DIE);

			auto* item = new BigBloodItem();
			m_listBullet.push_back(item);
			item->SetPosition(m_posX, m_posY);
			item->SetObjectType(BaseObject::OBJECT_ITEM);
			return;
		}

		if (m_shurikeinState == SHURIKEIN_ATTACK_2 && m_genjiboState == GENJIBO_MOVE)
		{
			m_genjiboState = GENJIBO_JUMP;
			m_vy = Define::ENEMY_MIN_JUMP_VELOCITY;
		}
	}
}

void Genjibo::OnCollision(eSideCollision side)
{
	switch (m_shurikeinState)
	{
	case SHURIKEIN_STAND:
		break;
	case SHURIKEIN_ATTACK_1:
	{
		//Attack Around
		if (m_sideX == BaseObject::SIDE_COLLISION_NONE && m_sideY != BaseObject::SIDE_COLLISION_NONE)
		{
			m_change = true;
			if (m_vy > 0)
				m_sideGen = BaseObject::SIDE_COLLISION_BOTTOM;
			else
				m_sideGen = BaseObject::SIDE_COLLISION_TOP;
		}
		else if (m_sideX != BaseObject::SIDE_COLLISION_NONE && m_sideY == BaseObject::SIDE_COLLISION_NONE)
		{
			m_change = true;
			if (m_vx > 0)
				m_sideGen = BaseObject::SIDE_COLLISION_RIGHT;
			else
				m_sideGen = BaseObject::SIDE_COLLISION_LEFT;
		}
		else if (m_sideX != BaseObject::SIDE_COLLISION_NONE && m_sideY != BaseObject::SIDE_COLLISION_NONE && m_change)
		{
			m_change = false;
			if (m_sideGen == SIDE_COLLISION_TOP || m_sideGen == SIDE_COLLISION_BOTTOM)
				m_vy *= -1;
			else
				m_vx *= -1;
		}
		else if (m_sideX == BaseObject::SIDE_COLLISION_NONE && m_sideY == BaseObject::SIDE_COLLISION_NONE && m_change)
		{
			m_change = false;
			if (m_sideGen == SIDE_COLLISION_TOP || m_sideGen == SIDE_COLLISION_BOTTOM)
				m_vx *= -1;
			else
				m_vy *= -1;
		}
		break;
	}

	case SHURIKEIN_ATTACK_2:
	case SHURIKEIN_ATTACK_3:
	{
		if (side == BaseObject::SIDE_COLLISION_BOTTOM)
			m_genjiboState = GENJIBO_MOVE;
		else
			if (side == BaseObject::SIDE_COLLISION_LEFT || side == BaseObject::SIDE_COLLISION_RIGHT)
				m_vx = -m_vx;
		break;
	}

	default:
		break;
	}
}

void Genjibo::Draw(Camera * camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	if (m_shurikeinState == SHURIKEIN_APPEAR)
	{
		m_animGenjinbo->SetPosition(m_posX, m_posY);
		m_animGenjinbo->Draw(m_animGenjinbo->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);
	}

	for (auto& bullet : m_listBullet)
		bullet->Draw(camera);

	if (m_isAllowDraw == false) return;

	if (m_isDie == true)
	{
		if (m_animDie->GetPause() == true)
			return;
		m_animDie->SetPosition(GetPosition());
		m_animDie->Draw(m_animDie->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);
	}
	else
	{
		m_anim->SetPosition(GetPosition());
		m_anim->Draw(m_anim->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);
	}
}

void Genjibo::SetState(eShurikeinState keinState)
{
	if (m_shurikeinState == keinState)
		return;

	m_shurikeinState = keinState;

	switch (m_shurikeinState)
	{
	case SHURIKEIN_APPEAR:
	{
		m_vx = 0;
		m_vy = 150;
		m_anim->SetAnimation(1, 10, 0.05);
		m_animGenjinbo->SetAnimation(0, 2, 0.05);
		m_posY = 920;
		break;
	}
	case SHURIKEIN_STAND:
	{
		m_vx = 0;
		m_vy = 150;
		m_anim->SetAnimation(7, 17, 0.005);
		break;
	}
	case SHURIKEIN_ATTACK_1:
	{
		m_vx = -150;
		m_vy = 150;
		m_sideGen = BaseObject::SIDE_COLLISION_BOTTOM;
		m_genjiboState = GENJIBO_UNKNOWN;
		m_anim->SetAnimation(5, 10, 0.03);
		break;
	}
	case SHURIKEIN_ATTACK_2:
	{
		m_genjiboState = GENJIBO_MOVE;
		m_anim->SetAnimation(6, 10, 0.03);
		m_vx = -150;
		m_vy = 150;
		break;
	}
	case SHURIKEIN_ATTACK_3:
	{
		m_genjiboState = GENJIBO_MOVE;
		m_anim->SetAnimation(7, 17, 0.01);
		m_vx = -80;
		m_vy = 150;
		break;
	}
	case SHURIKEIN_DIE:
		m_animDie->SetAnimation(0, 8, 0.05, false);
		m_vx = 0;
		m_vy = 0;
		break;
	default:
		break;
	}

	m_width = m_anim->GetWidth();
	m_height = m_anim->GetHeight();
}

void Genjibo::UpdateState(float dt)
{
	switch (m_shurikeinState)
	{
	case SHURIKEIN_APPEAR:
	{
		if (m_posY >= m_posY - 8)
		{
			m_posY = m_posY - 8;
			if (m_animGenjinbo->GetCurrentRow() != 1)
			{
				m_animGenjinbo->SetAnimation(1, 2, 0.05);
				m_isAllowDraw = true;
			}
			m_timeMove += dt;
			if (m_timeMove > 2)
			{
				m_timeMove = 0;
				SetState(SHURIKEIN_STAND);
				return;
			}
		}
		else
			m_posY += 100 * dt;

		break;
	}
	case SHURIKEIN_STAND:
	{
		m_vx = 0;
		m_vy = 150;
		m_timeStand += dt;
		if (m_timeStand > 2.0f)
		{
			m_timeStand = 0.0f;
			int Num = m_count % 3;
			m_count++;
			if (Num == 0)
				SetState(SHURIKEIN_ATTACK_1);
			else if (Num == 1)
				SetState(SHURIKEIN_ATTACK_2);
			else
				SetState(SHURIKEIN_ATTACK_3);
		}
		break;
	}
	case SHURIKEIN_ATTACK_1:
	{
		m_timeMove += dt;
		if (m_timeMove > 6)
		{
			m_timeMove = 0;
			SetState(SHURIKEIN_STAND);
			return;
		}
		break;
	}
	case SHURIKEIN_ATTACK_2:
	case SHURIKEIN_ATTACK_3:
	{
		m_timeMove += dt;
		if (m_timeMove > 6)
		{
			m_timeMove = 0;
			SetState(SHURIKEIN_STAND);
			return;
		}
		switch (m_genjiboState)
		{
		case GENJIBO_MOVE:
			m_vy = 150;
			if (m_shurikeinState == SHURIKEIN_ATTACK_3)
			{
				m_genjiboState = GENJIBO_JUMP;
				m_vy = Define::ENEMY_MIN_JUMP_VELOCITY;
				return;
			}
			break;
		case GENJIBO_JUMP:
		{
			AddVy(m_transY);
			if (m_vy > Define::ENEMY_MAX_JUMP_VELOCITY)
				m_vy = Define::ENEMY_MAX_JUMP_VELOCITY;
		}
		default:
			break;
		}
		break;
	}
	default:
		break;
	}

}
