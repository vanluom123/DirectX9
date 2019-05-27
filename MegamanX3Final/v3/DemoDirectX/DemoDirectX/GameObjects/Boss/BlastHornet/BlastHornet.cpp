#include "BlastHornet.h"
#include "BlastDie.h"
#include "Move.h"
#include "BlastStand.h"
#include "BlastAppear.h"
#include "../../../GameDefines/GameDefine.h"

BlastHornet::BlastHornet()
{
	m_objectType = eObjectType::OBJECT_BOSS;
	m_MaxHP = 30;
	m_Damage = 3;
	m_HP = m_MaxHP;
	m_currentState = BLAST_STATE_UNKNOWN;
	m_HPBar = new HPBar(m_objectType);

	m_blastHornetData = new BlastHornetData;
	m_blastHornetData->blastHornet = this;
	m_blastHornetData->blastHornetState = NULL;

	this->SetState(new BlastAppear(m_blastHornetData));
}


BlastHornet::~BlastHornet()
{
	delete m_anim;
	delete m_blastHornetData;
	for (auto&i : m_listBlastBullet)
		delete i;
	m_listBlastBullet.clear();
}

RECT BlastHornet::GetBound()
{
	RECT bound;
	bound.left = m_posX - 20;
	bound.right = m_posX + 30;
	bound.top = m_posY - 30;
	bound.bottom = m_posY + 45;
	return bound;
}

void BlastHornet::Update(float dt)
{
	for (auto&i : m_listBlastBullet)
		i->Update(dt);

	if (!m_isAllowDraw)
		return;

	m_anim->Update(dt);
	BaseObject::Update(dt);

	if (m_blastHornetData->blastHornetState)
		m_blastHornetData->blastHornetState->Update(dt);
}

void BlastHornet::OnCollision(eSideCollision side)
{
	if (m_blastHornetData->blastHornetState) 
		m_blastHornetData->blastHornetState->OnCollision(side);
}

void BlastHornet::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() == eObjectType::OBJECT_ROCK_MAN_BULLET && !m_isDie)
	{
		m_HP -= 1 + obj->GetDamage() / 2;
			
		if (m_HP <= 0)
		{
			SetState(new BlastDie(m_blastHornetData));
			m_isDie = true;
		}
	}
}

void BlastHornet::Draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotate, D3DCOLOR color)
{
	for (auto& i : m_listBlastBullet)
		i->Draw(camera, r, scale, angle, rotate, color);

	m_HPBar->draw(m_HP, m_MaxHP);

	if (!m_isAllowDraw)
		return;

	m_anim->SetPosition(GetPosition());
	m_anim->SetReverse(m_isReverse);
	if (camera)
		m_anim->Draw(m_anim->GetPosition(), r, scale, camera->GetTrans(), angle, rotate, color);
	else
		m_anim->Draw(m_anim->GetPosition());
}

void BlastHornet::SetState(BlastHornetState* newState)
{
	if (m_currentState == newState->GetState())
		return;

	SAFE_DELETE(m_blastHornetData->blastHornetState);
	m_blastHornetData->blastHornetState = newState;
	m_currentState = newState->GetState();
	ChangeAnimation(newState->GetState());
}

void BlastHornet::ChangeAnimation(eBlastState state)
{
	if (state == BLAST_STATE_STAND || state == BLAST_STATE_MOVE)
	{
		m_anim = new Animation("Resources/Enemies/BlastHornet/State/Stand/standspritesheet.png", 1, 4, 96, 96, 0.05, D3DCOLOR_XRGB(0, 128, 128));
		m_anim->SetAnimation(0, 4, 0.05);
	}
	else if (state == BLAST_STATE_APPEAR)
	{
		m_anim = new Animation("Resources/Enemies/BlastHornet/State/Appear/AppearSpriteSheet.png", 4, 9, 102, 104, 0.05, D3DCOLOR_XRGB(0, 128, 128));
		//anim->setAnim(36, 4, 9, 0.015, 0, false);
	}
	else if (state == BLAST_STATE_ATTACK)
	{
		m_anim = new Animation("Resources/Enemies/BlastHornet/State/Attack/attackspritesheet.png", 4, 9, 102, 104, 0.05, D3DCOLOR_XRGB(0, 128, 128));
		//anim->setAnim(36, 4, 9, 0.05, 0, false);
	}
	else if (state == BLAST_STATE_SHOOTER)
	{
		m_anim = new Animation("Resources/Enemies/BlastHornet/State/Shooter/shooterspirtesheet.png", 1, 15, 96, 96, 0.05, D3DCOLOR_XRGB(0, 128, 128));
		m_anim->SetAnimation(0, 15, 0.05, false);
	}
	else if (state == BLAST_STATE_DIE)
	{
		m_anim = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.05);
		m_anim->SetAnimation(0, 8, 0.05, false);
	}

	this->SetWidth(m_anim->GetWidth());
	this->SetHeight(m_anim->GetHeight());
}

Animation* BlastHornet::GetAnimation() const
{
	return m_anim;
}

std::vector<BlastBullet*>* BlastHornet::GetListBullet()
{
	return &m_listBlastBullet;
}
