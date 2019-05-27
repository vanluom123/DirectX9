#include "BlastBullet.h"
#include "../../../GameComponents/Camera.h"

BlastBullet::BlastBullet()
{
	m_objectType = eObjectType::OBJECT_ENEMY_BULLET;
	m_isReverse = true;
	m_Damage = 3;
	m_MaxHP = 4;
	m_HP = m_MaxHP;

	this->ChangeState(eBulletState::BULLET_FIRE);
}

BlastBullet::~BlastBullet()
{
	delete m_anim;
}

RECT BlastBullet::GetBound()
{
	RECT bound;
	bound.left = m_posX - m_width / 2;
	bound.top = m_posY - m_height / 2;
	bound.right = bound.left + m_width;
	bound.bottom = bound.top + m_height;
	return bound;
}

void BlastBullet::NewEntity()
{
	if (m_isReverse == false)
	{
		SetReverse(true);
		SetVx(-80);
	}
	else
	{
		SetReverse(false);
		SetVx(80);
	}

	//isBurst = false;
	m_isAllowDraw = true;
	ChangeState(eBulletState::BULLET_FIRE);
}

void BlastBullet::Update(float dt)
{
	if (m_isAllowDraw == false)
		return;

	//if (!isBurst)
	//{
	//	//vx += accelerateX;
	//	if (vx > 300)
	//		vx = 300;
	//	else if (vx < -300)
	//		vx = -300;
	//}
	//else if (anim->getPause())
	//	allowDraw = false;

	m_anim->Update(dt);
	BaseObject::Update(dt);
}

void BlastBullet::OnCollision(eSideCollision side)
{
	m_vx = 0;
	m_vy = 0;
	//isBurst = true;
	ChangeState(eBulletState::BULLET_EXPLOSION);
}

void BlastBullet::OnCollision(BaseObject* obj)
{
	OnCollision(eSideCollision::SIDE_COLLISION_NONE);
}

void BlastBullet::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (m_isAllowDraw == false)
		return;

	m_anim->SetPosition(GetPosition());
	m_anim->SetReverse(m_isReverse);
	if (camera)
		m_anim->Draw(GetPosition(), rect, scale, camera->GetTrans(), 0, rotationCenter, color);
	else
		m_anim->Draw(GetPosition());
}

void BlastBullet::ChangeState(eBulletState state)
{
	switch (state)
	{
	case BULLET_EXPLOSION:
		m_anim = new Animation("Resources/Enemies/BlastHornet/Burst/BurstAnimation.png", 1, 6, 34, 34, 0.05, D3DCOLOR_XRGB(6, 113, 158));
		m_anim->SetAnimation(0, 6, 0.05, false);
		break;

	case BULLET_FIRE:
		m_anim = new Animation("Resources/Enemies/BlastHornet/Bullet/BulletAnim.png", 1, 3, 24, 22, 0.05, D3DCOLOR_XRGB(6, 113, 158));
		m_anim->SetAnimation(0, 3);
		break;

	default:break;
	}

	m_width = m_anim->GetWidth();
	m_height = m_anim->GetHeight();

	m_bulletState = state;
}
