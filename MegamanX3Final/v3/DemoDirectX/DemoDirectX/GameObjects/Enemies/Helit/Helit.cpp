#include "Helit.h"
#include "../../../GameDefines/GameDefine.h"
#include "HelitState/HelitDie/HelitDie.h"
#include "HelitState/HelitStand/HelitStand.h"
#include "../../../GameComponents/GameCollision.h"
#include "../../Item/SmallBlood.h"
#include "../../Item/SmallSubtankItem.h"

Helit::Helit()
{
	m_objectType = OBJECT_ENEMY;
	m_anim = new Animation(Define::HELIT_SPRITE_SHEET, 2, 4, 39, 37, 0.1, D3DCOLOR_XRGB(100, 100, 100));
	m_animDie = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	m_isReverse = false;
	m_isDie = false;
	m_isAllowDraw = true;
	m_MaxHP = 4;
	m_HP = m_MaxHP;
	m_Damage = 3;
	m_currentState = HELIT_UNKNOWN;

	m_helitData = new HelitData;
	m_helitData->helit = this;
	m_helitData->helitState = NULL;

	this->SetState(new HelitStand(m_helitData));
}

void Helit::NewEntity()
{
	m_posX = m_startx;
	m_posY = m_starty;

	m_isReverse = false;
	m_isDie = false;
	m_isAllowDraw = true;
	m_HP = m_MaxHP;
	m_currentState = HELIT_UNKNOWN;
	SetState(new HelitStand(m_helitData));
}

Helit::~Helit()
{
	delete m_helitData;
	delete m_anim;
	delete m_animDie;
	for (auto& bullet : m_listBullet)
		delete bullet;
	m_listBullet.clear();
}

RECT Helit::GetBound()
{
	RECT bound;

	bound.left = m_posX - 19;
	bound.right = m_posX + 19;
	bound.top = m_posY - 18;
	bound.bottom = m_posY + 37 / 2.0f;

	return bound;
}

void Helit::Update(float dt)
{
	for (auto& bullet : m_listBullet)
		bullet->Update(dt);

	if (m_isAllowDraw == false)
		return;

	BaseObject::Update(dt);

	if (m_isDie == true)
		m_animDie->Update(dt);
	else
		m_anim->Update(dt);

	if (m_helitData->helitState != NULL)
		m_helitData->helitState->Update(dt);
}

void Helit::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() == BaseObject::OBJECT_ROCK_MAN_BULLET && m_isDie == false)
	{
		m_HP -= obj->GetDamage();
		if (m_HP <= 0)
		{
			m_isDie = true;
			SetState(new HelitDie(m_helitData));
		}

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

void Helit::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
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
		m_animDie->SetPosition(this->GetPosition());

		if (camera != NULL)
			m_animDie->Draw(m_animDie->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		else
			m_animDie->Draw(m_animDie->GetPosition());
	}
	else
	{
		m_anim->SetReverse(m_isReverse);
		m_anim->SetPosition(this->GetPosition());

		if (camera != NULL)
			m_anim->Draw(m_anim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		else
			m_anim->Draw(m_anim->GetPosition());
	}
}

void Helit::SetState(HelitState* newState)
{
	if (m_currentState == newState->GetState())
		return;

	SAFE_DELETE(m_helitData->helitState);

	m_helitData->helitState = newState;
	m_currentState = newState->GetState();
	ChangeAnimation(newState->GetState());
}

void Helit::ChangeAnimation(eHelitState state)
{
	switch (state)
	{
	case HELIT_STAND:
		m_anim->SetAnimation(0, 4, 0.15);
		m_anim->SetFrame(39, 36);
		break;

	case HELIT_ATTACK:
		m_anim->SetAnimation(1, 4, 0.15);
		m_anim->SetFrame(39, 36);
		break;

	case HELIT_DIE:
		m_animDie->SetAnimation(0, 8, 0.05, false);
		break;

	default: break;
	}

	m_width = m_anim->GetWidth();
	m_height = m_anim->GetHeight();
}
