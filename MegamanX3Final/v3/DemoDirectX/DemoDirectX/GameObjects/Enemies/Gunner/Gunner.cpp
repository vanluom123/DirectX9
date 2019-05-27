#include "Gunner.h"
#include "../../../GameDefines/GameDefine.h"
#include "GunnerState/GunnerFall/GunnerFall.h"
#include "../../Player/Player.h"
#include "GunnerState/GunnerDie/GunnerDie.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/SmallBlood.h"
#include "../../Item/SmallSubtankItem.h"

Gunner::Gunner()
{
	m_objectType = OBJECT_ENEMY;
	m_anim = new Animation(Define::HEAD_GUNNER_SPRITE, 4, 4, 51, 45, 0.15, D3DCOLOR_XRGB(100, 100, 100));
	m_animDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	m_isReverse = false;
	m_isAllowDraw = true;
	m_isDie = false;
	m_MaxHP = 6;
	m_Damage = 3;
	m_HP = m_MaxHP;
	m_curState = GUNNER_NONE;

	// Initialization GunnerData
	m_gunnerData = new GunnerData;
	m_gunnerData->gunner = this;
	m_gunnerData->gunnerState = NULL;

	this->SetState(new GunnerFall(m_gunnerData));
}

void Gunner::NewEntity()
{
	m_posX = m_startx;
	m_posY = m_starty;
	m_isReverse = false;
	m_isAllowDraw = true;
	m_isDie = false;
	m_HP = m_MaxHP;
	m_curState = GUNNER_NONE;
	SetState(new GunnerFall(m_gunnerData));
}

Gunner::~Gunner()
{
	delete m_anim;
	delete m_animDie;
	delete m_gunnerData;
	for (auto& bullet : m_listBullet)
		delete bullet;
	m_listBullet.clear();
}

RECT Gunner::GetBound()
{
	RECT bound;

	bound.left = m_posX - 15;
	bound.right = m_posX + 15;
	bound.top = m_posY - 21;
	bound.bottom = m_posY + 45 / 2.0f;

	return bound;
}

void Gunner::Update(float dt)
{
	OnNoCollisionWithBottom();

	for (auto& bullet : m_listBullet)
		bullet->Update(dt);

	if (m_isAllowDraw == false)
		return;

	m_anim->Update(dt);
	m_animDie->Update(dt);
	BaseObject::Update(dt);

	if (m_gunnerData->gunnerState != NULL)
		m_gunnerData->gunnerState->Update(dt);
}

void Gunner::OnCollision(eSideCollision side)
{
	if (m_gunnerData->gunnerState)
		m_gunnerData->gunnerState->OnCollision(side);
}

void Gunner::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() == BaseObject::OBJECT_ROCK_MAN_BULLET && !m_isDie)
	{
		m_HP -= obj->GetDamage();
		if (m_HP <= 0)
		{
			m_isDie = true;
			this->SetState(new GunnerDie(m_gunnerData));

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

void Gunner::OnNoCollisionWithBottom()
{
	if (m_sideY != SIDE_COLLISION_BOTTOM)
	{
		switch (m_curState)
		{
		case GUNNER_STAND:
		case GUNNER_ATTACK:
		case GUNNER_ATTACK_ROCKET:
		case GUNNER_ATTACK_BULLET:
			SetState(new GunnerFall(m_gunnerData));
			break;
		default: break;
		}
	}
}

void Gunner::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
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
			m_animDie->Draw(m_animDie->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		else
			m_animDie->Draw(m_animDie->GetPosition());
	}
	else
	{
		m_anim->SetReverse(m_isReverse);
		m_anim->SetPosition(GetPosition());

		if (camera != NULL)
			m_anim->Draw(m_anim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		else
			m_anim->Draw(m_anim->GetPosition());
	}
}

void Gunner::ChangeAnimation(eGunnerState stateName)
{
	switch (stateName)
	{
	case GUNNER_STAND:
		m_anim->SetAnimation(0, 1);
		break;

	case GUNNER_ATTACK:
		m_anim->SetAnimation(2, 3, 0.15, false);
		break;

	case GUNNER_ATTACK_ROCKET:
		m_anim->SetAnimation(1, 3, 0.15, false);
		break;

	case GUNNER_ATTACK_BULLET:
		m_anim->SetAnimation(0, 1);
		break;

	case GUNNER_FALL:
		m_anim->SetAnimation(0, 1);
		break;

	case GUNNER_DIE:
		m_animDie->SetAnimation(0, 8, 0.05, false);
		break;

	default: break;
	}

	this->SetWidth(m_anim->GetWidth());
	this->SetHeight(m_anim->GetHeight());
}

void Gunner::SetState(GunnerState* state)
{
	if (m_curState == state->GetState())
		return;

	SAFE_DELETE(m_gunnerData->gunnerState);

	m_gunnerData->gunnerState = state;
	m_curState = state->GetState();
	this->ChangeAnimation(state->GetState());
}
