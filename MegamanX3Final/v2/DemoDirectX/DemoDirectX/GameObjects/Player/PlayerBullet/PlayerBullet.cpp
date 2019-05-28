#include "PlayerBullet.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/Camera.h"
#include "../../../GameComponents/GameCollision.h"

PlayerBullet::PlayerBullet()
{
	_objectType = ROCK_MAN_BULLET;
	_bulletX = 25.0f;

	// GAME DEBUG
	//_gameDebug = new GameDebugDraw();
}

PlayerBullet::~PlayerBullet()
{
	SAFE_DELETE(_pAnim);
}

void PlayerBullet::NewBullet(float bx, float by, bool direction, eBulletType type)
{
	_posX = bx;
	_posY = by;
	_isAllowDraw = true;
	_isExplosions = false;
	_bulletState = BULLET_STATE_FIRE;
	_bulletType = type;

	SetReverse(direction);
	if (direction == true)
		_vx = -300;
	else
		_vx = 300;

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
			_Damage = 1;
			_pAnim = new Animation("Resources/rockman/bullet.png", 1, 1, 8, 6);
			break;

		case BULLET_TYPE_FIRST_LEVEL:
			_Damage = 2;
			_pAnim = new Animation("Resources/rockman/bullet_level_1.png", 1, 5, 46, 24, 0.15f);
			break;

		case BULLET_TYPE_SECOND_LEVEL:
			_Damage = 4;
			_pAnim = new Animation("Resources/rockman/bullet_level_2.png", 1, 4, 46, 31, 0.15f);
			break;

		default: break;
		}
	}
	case BULLET_STATE_EXPLOSION:
	{
		switch (type)
		{
		case BULLET_TYPE_EXPLOSION_NORMAL:
			_pAnim = new Animation("Resources/rockman/explosions_bullet.png", 1, 2, 15, 15, 0.05f);
			_pAnim->SetLoop(false);
			break;

		case BULLET_TYPE_EXPLOSION_FIRST_LEVEL:
			_pAnim = new Animation("Resources/rockman/explosion_level_1.png", 1, 2, 24, 24, 0.05f);
			_pAnim->IsAnchorPoint(true);
			if (_isReverse)
				_pAnim->SetAnchorPoint(1.0f, 1.0f);
			else
				_pAnim->SetAnchorPoint(1.0f, 1.0f);
			_pAnim->SetLoop(false);
			break;

		case BULLET_TYPE_EXPLOSION_SECOND_LEVEL:
			_pAnim = new Animation("Resources/rockman/explosions_level_2.png", 1, 2, 24, 26, 0.05f);
			_pAnim->SetLoop(false);
			break;

		default: break;
		}
	}

	default: break;

	}

	_width = _pAnim->GetWidth();
	_height = _pAnim->GetHeight();
}

RECT PlayerBullet::GetBound()
{
	RECT bound;
	bound.left = _posX - _width / 2;
	bound.top = _posY - _height / 2;
	bound.right = bound.left + _width;
	bound.bottom = bound.top + _height;
	return bound;
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
	{
		_pAnim->Draw(GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		//_gameDebug->DrawRect(rect, camera);
	}
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
	_bulletState = BULLET_STATE_EXPLOSION;

	switch (_bulletType)
	{
	case BULLET_TYPE_NORMAL:
		_bulletType = BULLET_TYPE_EXPLOSION_NORMAL;
		break;

	case BULLET_TYPE_FIRST_LEVEL:
		_bulletType = BULLET_TYPE_EXPLOSION_FIRST_LEVEL;
		break;

	case BULLET_TYPE_SECOND_LEVEL:
		_bulletType = BULLET_TYPE_EXPLOSION_SECOND_LEVEL;
		break;

	default: break;
	}

	ChangeBullet(_bulletState, _bulletType);
}