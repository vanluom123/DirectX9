#include "PlayerBullet.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/Camera.h"
#include "../../../GameComponents/GameCollision.h"

PlayerBullet::PlayerBullet()
{
	_objectType = ROCK_MAN_BULLET;
	_bulletX = 25.0f;
}

PlayerBullet::~PlayerBullet()
{
	SAFE_DELETE(_pAnim);
}

void PlayerBullet::NewBullet(float bx, float by, bool direction, BulletType type)
{
	_posX = bx;
	_posY = by;
	_isAllowDraw = true;
	_isExplosions = false;
	_bulletState = FIRE;
	_bulletType = type;

	SetReverse(direction);
	if (direction == true)
		_vx = -300;
	else
		_vx = 300;

	ChangeBullet(FIRE, type);
}

void PlayerBullet::ChangeBullet(BulletState state, BulletType type)
{
	switch (state)
	{
	default: break;

	case FIRE:
	{
		switch (type)
		{
		case NORMAL:
			_Damage = 1;
			_pAnim = new Animation("Resources/rockman/bullet.png", 1, 1, 8, 6);
			break;

		case FIRST_LEVEL:
			_Damage = 2;
			_pAnim = new Animation("Resources/rockman/bullet_level_1.png", 1, 5, 46, 24, 0.15);
			break;

		case SECOND_LEVEL:
			_Damage = 4;
			_pAnim = new Animation("Resources/rockman/bullet_level_2.png", 1, 4, 46, 31, 0.15);
			break;

		default: break;
		}
	}
	case EXPLOSIONS:
	{
		switch (type)
		{
		case EXPLOSIONS_NORMAL:
			_pAnim = new Animation("Resources/rockman/explosions_bullet.png", 1, 2, 15, 15, 0.15);
			_pAnim->SetLoop(false);
			break;

		case EXPLOSIONS_FIRST_LEVEL:
			_pAnim = new Animation("Resources/rockman/explosion_level_1.png", 1, 2, 24, 24, 0.15);
			_pAnim->SetLoop(false);
			break;

		case EXPLOSIONS_SECOND_LEVEL:
			_pAnim = new Animation("Resources/rockman/explosions_level_2.png", 1, 2, 24, 26, 0.15);
			_pAnim->SetLoop(false);
			break;

		default: break;
		}
	}
	}

	_width = _pAnim->GetWidth();
	_height = _pAnim->GetHeight();
}

RECT PlayerBullet::GetBound()
{
	RECT r = RECT();

	switch (_bulletState)
	{
	case FIRE:
	{
		switch (_bulletType)
		{
		case NORMAL:
			r.left = _posX;
			r.top = _posY;
			r.right = r.left + 8;
			r.bottom = r.top + 6;
			break;

		case FIRST_LEVEL:
			if (_isReverse)
			{
				
			}
			else
			{
				r.left = _posX + 10;
				r.top = _posY + 7;
				r.right = r.left + 46;
				r.bottom = r.top + 24;
			}
			
			break;

		case SECOND_LEVEL:
			r.left = _posX + 13;
			r.top = _posY + 6;
			r.right = r.left + 46;
			r.bottom = r.top + 31;
			break;

		default: break;
		}
	}
	case EXPLOSIONS:
	{
		switch (_bulletType)
		{
		case EXPLOSIONS_NORMAL:
			r.left = _posX + 1;
			r.top = _posY + 1;
			r.right = r.left + 15;
			r.bottom = r.top + 15;
			break;

		case EXPLOSIONS_FIRST_LEVEL:
			r.left = _posX + 5;
			r.top = _posY + 5;
			r.right = r.left + 24;
			r.bottom = r.top + 24;
			break;

		case EXPLOSIONS_SECOND_LEVEL:
			r.left = _posX + 5;
			r.top = _posY + 4;
			r.right = r.left + 24;
			r.bottom = r.top + 26;
			break;

		default: break;
		}
	}

	default: break;
	}

	return r;
}

void PlayerBullet::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (GameCollision::IsCollision(GetBound(), camera->GetBound()) == false)
	{
		_isAllowDraw = false;
		_isExplosions = true;
	}

	if (_isAllowDraw == false)
		return;

	_pAnim->SetReverse(_isReverse);
	_pAnim->SetPosition(GetPosition());

	if (camera != NULL)
		_pAnim->Draw(GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
	else
		_pAnim->Draw(GetPosition());
}

void PlayerBullet::Update(float dt)
{
	if (_isAllowDraw == false)
		return;

	if (_pAnim->GetPause() == true)
		_isAllowDraw = false;

	BaseObject::Update(dt);
	_pAnim->Update(dt);
}

void PlayerBullet::OnCollision(eSideCollision side)
{}

void PlayerBullet::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() != ENEMY
		&& obj->GetObjectType() != BOSS
		&& obj->GetObjectType() != BOX)
		return;

	if (obj->GetHP() <= 0)
		return;

	_isExplosions = true;
	_vx = _vy = 0;
	_bulletState = EXPLOSIONS;

	switch (_bulletType)
	{
	case NORMAL:
		_bulletType = EXPLOSIONS_NORMAL;
		break;

	case FIRST_LEVEL:
		_bulletType = EXPLOSIONS_FIRST_LEVEL;
		break;

	case SECOND_LEVEL:
		_bulletType = EXPLOSIONS_SECOND_LEVEL;
		break;

	default: break;
	}

	ChangeBullet(_bulletState, _bulletType);
}