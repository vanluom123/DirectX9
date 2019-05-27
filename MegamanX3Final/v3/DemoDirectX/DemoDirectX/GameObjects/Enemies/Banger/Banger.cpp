#include "Banger.h"
#include "../../../GameDefines/GameDefine.h"
#include "BangerState/BangerFall/BangerFall.h"
#include "BangerState/BangerDie/BangerDie.h"
#include "BangerState/BangerStand/BangerStand.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/SmallBlood.h"
#include "../../Item/SmallSubtankItem.h"

Banger::Banger()
{
	m_objectType = OBJECT_ENEMY;
	m_animDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	m_currentAnim = new Animation(Define::NOTOR_BANGER_SPRITE, 3, 4, 48, 48);
	m_MaxHP = 4;
	m_HP = m_MaxHP;
	m_Damage = 3;
	m_isReverse = true;
	m_isAllowDraw = true;
	m_isDie = false;
	m_currentState = BANGER_NONE;

	m_bangerData = new BangerData;
	m_bangerData->banger = this;
	m_bangerData->bangerState = NULL;

	this->SetState(new BangerFall(m_bangerData));
}

void Banger::NewEntity()
{
	m_posX = m_startx;
	m_posY = m_starty;
	m_HP = m_MaxHP;
	m_isReverse = true;
	m_isAllowDraw = true;
	m_isDie = false;
	m_currentState = BANGER_NONE;
	this->SetState(new BangerFall(m_bangerData));
}

Banger::~Banger()
{
	delete m_bangerData;
	delete m_currentAnim;
	delete m_animDie;
	for (auto& bullet : m_listBullet)
		delete bullet;
	m_listBullet.clear();
}

void Banger::ChangeAnimation(eBangerState state)
{
	switch (state)
	{
	case eBangerState::BANGER_STAND:
		m_currentAnim->SetAnimation(0, 2, 0.1f);
		break;

	case eBangerState::BANGER_JUMP:
		m_currentAnim->SetAnimation(1, 2, 0.15f, false);
		break;

	case eBangerState::BANGER_FALL:
		m_currentAnim->SetAnimation(1, 2, 0.15f, false);
		break;

	case eBangerState::BANGER_ATTACK:
		m_currentAnim->SetAnimation(2, 3, 0.15f, false);
		break;

	case BANGER_DIE:
		m_animDie->SetAnimation(0, 8, 0.05f, false);
		break;

	default: break;
	}

	this->SetWidth(m_currentAnim->GetWidth());
	this->SetHeight(m_currentAnim->GetHeight());
}


void Banger::SetState(BangerState * newState)
{
	if (m_currentState == newState->GetStateName())
		return;

	SAFE_DELETE(m_bangerData->bangerState);

	m_bangerData->bangerState = newState;
	m_currentState = newState->GetStateName();
	ChangeAnimation(newState->GetStateName());
}

RECT Banger::GetBound()
{
	RECT bound;

	bound.left = m_posX - 15;
	bound.right = m_posX + 15;
	bound.top = m_posY - 20;
	bound.bottom = m_posY + 48 / 2.0f;

	return bound;
}

void Banger::Draw(Camera * camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR transColor)
{
	if (m_isDie == false)
	{
		if (GameCollision::IsCollision(this->GetBound(), camera->GetBound()) == false)
			m_isAllowDraw = false;
		else
			m_isAllowDraw = true;
	}

	for (auto& bullet : m_listBullet)
		bullet->Draw(camera);

	if (m_isAllowDraw == false)
		return;

	if (m_isDie == true)
	{
		m_animDie->SetPosition(GetPosition());

		if (camera != NULL)
			m_animDie->Draw(m_animDie->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, transColor);
		else
			m_animDie->Draw(m_animDie->GetPosition());
	}
	else
	{
		m_currentAnim->SetReverse(m_isReverse);
		m_currentAnim->SetPosition(GetPosition());

		if (camera != NULL)
			m_currentAnim->Draw(m_currentAnim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, transColor);
		else
			m_currentAnim->Draw(m_currentAnim->GetPosition());
	}
}

void Banger::Update(float gameTime)
{
	OnNoCollisionWithBottom();

	for (auto& bullet : m_listBullet)
		bullet->Update(gameTime);

	if (m_isAllowDraw == false)
		return;

	m_currentAnim->Update(gameTime);
	m_animDie->Update(gameTime);
	BaseObject::Update(gameTime);

	if (m_bangerData->bangerState != NULL)
		m_bangerData->bangerState->Update(gameTime);
}

void Banger::OnCollision(eSideCollision side)
{
	if (m_bangerData->bangerState != NULL)
		m_bangerData->bangerState->OnCollision(side);
}

void Banger::OnCollision(BaseObject * obj)
{
	if (obj->GetObjectType() == BaseObject::OBJECT_ROCK_MAN_BULLET && !m_isDie)
	{
		m_HP -= obj->GetDamage();
		if (m_HP <= 0)
		{
			m_isDie = true;
			this->SetState(new BangerDie(m_bangerData));

			//
			int num = (rand() % 999) % 4;
			if (num == 1)
			{
				auto* item = new SmallBloodItem();
				m_listBullet.push_back(item);
				item->SetPosition(m_posX, m_posY);
				item->SetObjectType(BaseObject::OBJECT_ITEM);
			}
			else if (num == 2)
			{
				auto* item = new SmallSubtankItem();
				m_listBullet.push_back(item);
				item->SetPosition(m_posX, m_posY);
				item->SetObjectType(BaseObject::OBJECT_ITEM);
			}
		}
	}
}

void Banger::OnNoCollisionWithBottom()
{
	if (m_sideY != SIDE_COLLISION_BOTTOM)
	{
		switch (m_currentState)
		{
		case BANGER_STAND:
		case BANGER_ATTACK:
			this->SetState(new BangerFall(m_bangerData));
			break;
		default:break;
		}
	}
}
