#include "HelitBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"

HelitBullet::HelitBullet()
{
	m_objectType = OBJECT_ENEMY_BULLET;
	m_anim = new Animation(Define::HELIT_BULLET, 1, 1, 15, 10);
	m_animExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	m_HP = 3;
	m_Damage = 2;
	this->ChangeState(BULLET_FIRE);

	m_isReverse = false;
	m_isDie = false;
	m_isAllowDraw = true;
	m_bulletX = 25.0f;
}

HelitBullet::~HelitBullet()
{
	delete m_anim;
	delete m_animExplosion;
}

void HelitBullet::NewEntity()
{
	if (m_isReverse == true)
	{
		SetReverse(true);
		SetVx(80);
		SetBulletX(25.0f);
	}
	else
	{
		SetReverse(false);
		SetVx(-80);
		SetBulletX(-25.0f);
	}

	this->ChangeState(BULLET_FIRE);
	m_isDie = false;
	m_isAllowDraw = true;
}

RECT HelitBullet::GetBound()
{
	RECT bound{};

	switch (m_bulletState)
	{
	case BULLET_FIRE:
		bound.left = m_posX - 7;
		bound.right = m_posX + 8;
		bound.top = m_posY - 5;
		bound.bottom = m_posY + 5;
		break;

	case BULLET_EXPLOSION:
		bound.left = m_posX - 25;
		bound.right = m_posX + 25;
		bound.top = m_posY - 22;
		bound.bottom = m_posY + 23;
		break;

	default: break;

	}

	return bound;
}

void HelitBullet::Update(float dt)
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

void HelitBullet::OnCollision(eSideCollision side)
{}

void HelitBullet::OnCollision(BaseObject * obj)
{
	if (obj->GetObjectType() == OBJECT_ENEMY)
		return;

	m_vx = 0;
	m_vy = 0;
	m_isDie = true;
	this->ChangeState(BULLET_EXPLOSION);
}

void HelitBullet::Draw(Camera * camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (GameCollision::IsCollision(camera->GetBound(), GetBound()) == false)
	{
		m_isAllowDraw = false;
		m_isDie = true;
	}

	if (m_isAllowDraw == false)
		return;

	switch (m_bulletState)
	{
	case BULLET_FIRE:
		m_anim->SetReverse(m_isReverse);
		m_anim->SetPosition(this->GetPosition());
		if (camera)
			m_anim->Draw(m_anim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		else
			m_anim->Draw(m_anim->GetPosition());
		break;

	case BULLET_EXPLOSION:
		m_animExplosion->SetPosition(this->GetPosition());
		if (camera)
			m_animExplosion->Draw(m_animExplosion->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		else
			m_animExplosion->Draw(m_animExplosion->GetPosition());
		break;

	default: break;
	}
}

void HelitBullet::ChangeState(eBulletState state)
{
	m_bulletState = state;

	switch (state)
	{
	case BULLET_FIRE:
		m_anim->SetAnimation(0, 1);
		this->SetWidth(m_anim->GetWidth());
		this->SetHeight(m_anim->GetHeight());
		break;

	case BULLET_EXPLOSION:
		m_animExplosion->SetAnimation(0, 8, 0.05f, false);
		this->SetWidth(m_animExplosion->GetWidth());
		this->SetHeight(m_animExplosion->GetHeight());
		break;

	default: break;
	}
}
