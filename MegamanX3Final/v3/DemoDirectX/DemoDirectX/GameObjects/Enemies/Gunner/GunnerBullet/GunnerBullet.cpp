#include "GunnerBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"

GunnerBullet::GunnerBullet()
{
	m_objectType = OBJECT_ENEMY_BULLET;
	m_anim = new Animation(Define::HEAD_GUNNER_BULLET, 1, 2, 23, 7, 0.1);
	m_animExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.1);

	m_isReverse = true;
	m_HP = 3;
	m_Damage = 3;
	m_bulletX = 25.0f;
	m_timeFire = 0.0f;

	this->ChangeState(BULLET_FIRE);
}

GunnerBullet::~GunnerBullet()
{
	delete m_anim;
	delete m_animExplosion;
}

RECT GunnerBullet::GetBound()
{
	RECT bound{};

	switch (m_bulletState)
	{
	case BULLET_EXPLOSION:
		bound.left = m_posX - 25;
		bound.right = m_posX + 25;
		bound.top = m_posY - 22;
		bound.bottom = m_posY + 23;
		break;

	case BULLET_FIRE:
		bound.left = m_posX - 10;
		bound.right = m_posX + 13;
		bound.top = m_posY - 3;
		bound.bottom = m_posY + 4;
		break;

	default: break;
	}

	return bound;
}

void GunnerBullet::NewEntity()
{
	if (m_isReverse == false)
	{
		SetReverse(false);
		SetVx(-80);
		SetBulletX(-25.0f);
	}
	else
	{
		SetReverse(true);
		SetVx(80);
		SetBulletX(25.0f);
	}

	this->ChangeState(BULLET_FIRE);
	m_isDie = false;
	m_isAllowDraw = true;
}

void GunnerBullet::Update(float dt)
{
	if (m_isAllowDraw == false)
		return;

	if (m_isDie == false)
	{
		m_vx += m_bulletX;
		if (m_vx > 300)
			m_vx = 300;
		else if (m_vx < -300)
			m_vx = -300;
	}
	else if (m_anim->GetPause() == true || m_animExplosion->GetPause() == true)
		m_isAllowDraw = false;

	if (m_bulletState == BULLET_EXPLOSION)
		m_animExplosion->Update(dt);
	else
		m_anim->Update(dt);

	BaseObject::Update(dt);
}

void GunnerBullet::OnCollision(eSideCollision side)
{}

void GunnerBullet::OnCollision(BaseObject * obj)
{
	if (obj->GetObjectType() == OBJECT_ENEMY)
		return;

	m_vx = 0;
	m_vy = 0;
	m_isDie = true;
	this->ChangeState(BULLET_EXPLOSION);
}

void GunnerBullet::Draw(Camera * camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (m_isAllowDraw == false)
		return;

	switch (m_bulletState)
	{
	case BULLET_EXPLOSION:
		m_animExplosion->SetPosition(this->GetPosition());
		if (camera)
			m_animExplosion->Draw(m_animExplosion->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		else
			m_animExplosion->Draw(m_animExplosion->GetPosition());
		break;

	default:
		m_anim->SetReverse(m_isReverse);
		m_anim->SetPosition(this->GetPosition());

		if (camera)
			m_anim->Draw(m_anim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		else
			m_anim->Draw(m_anim->GetPosition());
		break;	
	}
}

void GunnerBullet::ChangeState(eBulletState state)
{
	m_bulletState = state;

	switch (state)
	{
	case BULLET_EXPLOSION:
		m_animExplosion->SetAnimation(0, 8, 0.05, false);
		this->SetWidth(m_animExplosion->GetWidth());
		this->SetHeight(m_animExplosion->GetHeight());
		break;

	default:
		m_anim->SetAnimation(0, 2);
		this->SetWidth(m_anim->GetWidth());
		this->SetHeight(m_anim->GetHeight());
		break;
	
	}
}
