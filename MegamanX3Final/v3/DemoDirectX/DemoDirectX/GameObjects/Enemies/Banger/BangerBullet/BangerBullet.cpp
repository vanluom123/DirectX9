#include "BangerBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"


BangerBullet::BangerBullet()
{
	m_objectType = OBJECT_ENEMY_BULLET;
	m_anim = new Animation(Define::NOTOR_BANGER_BULLET, 2, 3, 8, 8, D3DCOLOR_XRGB(0, 100, 100));
	m_animExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.1f);
	this->ChangeState(BULLET_FIRE);
	m_HP = 3;
	m_Damage = 2;
	m_bulletY = 25.0f;
	m_isAllowDraw = true;
}

BangerBullet::~BangerBullet()
{
	delete m_anim;
	delete m_animExplosion;
}

RECT BangerBullet::GetBound()
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
		bound.left = m_posX - 4;
		bound.top = m_posY - 4;
		bound.right = m_posX + 4;
		bound.bottom = m_posY + 4;
		break;

	default: break;
	}

	return bound;
}

void BangerBullet::NewEntity()
{
	m_objectType = OBJECT_ENEMY_BULLET;
	m_vy = -450;
	if (m_isReverse == true)
	{
		//vx = 70;
		m_vx = 100;

	}
	else
	{
		//vx = -70;
		m_vx = -100;

	}
	ChangeState(BULLET_FIRE);
	m_isDie = false;
	m_isAllowDraw = true;
}

void BangerBullet::Update(float dt)
{
	if (m_isAllowDraw == false)
		return;

	if (m_isDie == false)
	{
		m_vy += m_bulletY;
		if (m_vy > 300)
			m_vy = 300;

	}
	else if (m_anim->GetPause() == true || m_animExplosion->GetPause() == true)// da chay xong animation no
		m_isAllowDraw = false;

	if (m_bulletState == BULLET_EXPLOSION)
		m_animExplosion->Update(dt);
	else
		m_anim->Update(dt);

	BaseObject::Update(dt);
}

void BangerBullet::OnCollision(eSideCollision side)
{}

void BangerBullet::OnCollision(BaseObject * obj)
{
	if (obj->GetObjectType() == OBJECT_ENEMY)
		return;
	m_vx = 0;
	m_vy = 0;
	m_isDie = true;
	ChangeState(BULLET_EXPLOSION);
}

void BangerBullet::ChangeState(eBulletState state)
{
	m_bulletState = state;

	switch (state)
	{
	case BULLET_EXPLOSION:
		m_animExplosion->SetAnimation(0, 8, 0.05, false);
		this->SetWidth(m_animExplosion->GetWidth());
		this->SetHeight(m_animExplosion->GetHeight());
		break;

	case BULLET_FIRE:
		m_anim->SetAnimation(0, 1);
		this->SetWidth(m_anim->GetWidth());
		this->SetHeight(m_anim->GetHeight());
		break;

	default: break;
	}
}