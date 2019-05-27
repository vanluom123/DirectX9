#include "PlayerBullet.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/Camera.h"
#include "../../../GameComponents/GameCollision.h"

PlayerBullet::PlayerBullet()
{
	m_objectType = OBJECT_ROCK_MAN_BULLET;
	m_playerBulletX = 25.0f;

	// GAME DEBUG
	//_gameDebug = new GameDebugDraw();
}

PlayerBullet::~PlayerBullet()
{
	SAFE_DELETE(m_anim);
}

void PlayerBullet::NewBullet(float bx, float by, bool direction, eBulletType type)
{
	m_posX = bx;
	m_posY = by;
	m_isAllowDraw = true;
	m_isExplosion = false;
	m_playerBulletState = BULLET_STATE_FIRE;
	m_playerBulletType = type;

	SetReverse(direction);
	if (direction == true)
		m_vx = -300;
	else
		m_vx = 300;

	this->ChangeBullet(BULLET_STATE_FIRE, type);
}

void PlayerBullet::ChangeBullet(eBulletState state, eBulletType type)
{
	switch (state)
	{

	case BULLET_STATE_FIRE:
	{
		switch (type)
		{
		case BULLET_TYPE_NORMAL:
			m_Damage = 1;
			m_anim = new Animation("Resources/rockman/bullet.png", 1, 1, 8, 6);
			break;

		case BULLET_TYPE_FIRST_LEVEL:
			m_Damage = 2;
			m_anim = new Animation("Resources/rockman/bullet_level_1.png", 1, 5, 46, 24, 0.15f);
			break;

		case BULLET_TYPE_SECOND_LEVEL:
			m_Damage = 4;
			m_anim = new Animation("Resources/rockman/bullet_level_2.png", 1, 4, 46, 31, 0.15f);
			break;

		default: break;
		}
	}
	case BULLET_STATE_EXPLOSION:
	{
		switch (type)
		{
		case BULLET_TYPE_EXPLOSION_NORMAL:
			m_anim = new Animation("Resources/rockman/explosions_bullet.png", 1, 2, 15, 15, 0.05f);
			m_anim->SetLoop(false);
			break;

		case BULLET_TYPE_EXPLOSION_FIRST_LEVEL:
			m_anim = new Animation("Resources/rockman/explosion_level_1.png", 1, 2, 24, 24, 0.05f);
			m_anim->IsAnchorPoint(true);
			if (m_isReverse)
				m_anim->SetAnchorPoint(1.0f, 1.0f);
			else
				m_anim->SetAnchorPoint(1.0f, 1.0f);
			m_anim->SetLoop(false);
			break;

		case BULLET_TYPE_EXPLOSION_SECOND_LEVEL:
			m_anim = new Animation("Resources/rockman/explosions_level_2.png", 1, 2, 24, 26, 0.05f);
			m_anim->SetLoop(false);
			break;

		default: break;
		}
	}

	default: break;

	}

	m_width = m_anim->GetWidth();
	m_height = m_anim->GetHeight();
}

RECT PlayerBullet::GetBound()
{
	RECT bound;
	bound.left = m_posX - m_width / 2;
	bound.top = m_posY - m_height / 2;
	bound.right = bound.left + m_width;
	bound.bottom = bound.top + m_height;
	return bound;
}

void PlayerBullet::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (GameCollision::IsCollision(GetBound(), camera->GetBound()) == false)
	{
		m_isAllowDraw = false;
		m_isExplosion = true;
	}

	if (m_isAllowDraw == false)
		return;

	m_anim->SetReverse(m_isReverse);
	m_anim->SetPosition(GetPosition());

	if (camera != NULL)
	{
		m_anim->Draw(GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		//_gameDebug->DrawRect(rect, camera);
	}
	else
		m_anim->Draw(GetPosition());
}

void PlayerBullet::Update(float dt)
{
	if (m_isAllowDraw == false)
		return;

	if (m_anim->GetPause() == true)
		m_isAllowDraw = false;

	BaseObject::Update(dt);
	m_anim->Update(dt);
}

void PlayerBullet::OnCollision(eSideCollision side)
{}

void PlayerBullet::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() != OBJECT_ENEMY
		&& obj->GetObjectType() != OBJECT_BOSS
		&& obj->GetObjectType() != OBJECT_BOX)
		return;

	if (obj->GetHP() <= 0)
		return;

	m_isExplosion = true;
	m_vx = 0;
	m_vy = 0;
	m_playerBulletState = BULLET_STATE_EXPLOSION;

	switch (m_playerBulletType)
	{
	case BULLET_TYPE_NORMAL:
		m_playerBulletType = BULLET_TYPE_EXPLOSION_NORMAL;
		break;

	case BULLET_TYPE_FIRST_LEVEL:
		m_playerBulletType = BULLET_TYPE_EXPLOSION_FIRST_LEVEL;
		break;

	case BULLET_TYPE_SECOND_LEVEL:
		m_playerBulletType = BULLET_TYPE_EXPLOSION_SECOND_LEVEL;
		break;

	default: break;
	}

	ChangeBullet(m_playerBulletState, m_playerBulletType);
}