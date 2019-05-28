#include "GunnerBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"

GunnerBullet::GunnerBullet()
{
	_objectType = ENEMY_BULLET;
	_pAnim = new Animation(Define::HEAD_GUNNER_BULLET, 1, 2, 23, 7, 0.1);
	_pAnimExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.1);

	_isReverse = true;
	_HP = 3;
	_Damage = 3;
	_bulletX = 25.0f;
	_timeFire = 0.0f;

	this->ChangeState(BULLET_FIRE);
}

GunnerBullet::~GunnerBullet()
{
	delete _pAnim;
	delete _pAnimExplosion;
}

RECT GunnerBullet::GetBound()
{
	RECT bound{};

	switch (_bulletState)
	{
	case BULLET_EXPLOSION:
		bound.left = _posX - 25;
		bound.right = _posX + 25;
		bound.top = _posY - 22;
		bound.bottom = _posY + 23;
		break;

	case BULLET_FIRE:
		bound.left = _posX - 10;
		bound.right = _posX + 13;
		bound.top = _posY - 3;
		bound.bottom = _posY + 4;
		break;

	default: break;
	}

	return bound;
}

void GunnerBullet::NewEntity()
{
	if (_isReverse == false)
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
	_isDie = false;
	_isAllowDraw = true;
}

void GunnerBullet::Update(float dt)
{
	if (_isAllowDraw == false)
		return;

	if (_isDie == false)
	{
		_vx += _bulletX;
		if (_vx > 300)
			_vx = 300;
		else if (_vx < -300)
			_vx = -300;
	}
	else if (_pAnim->GetPause() == true || _pAnimExplosion->GetPause() == true)
		_isAllowDraw = false;

	if (_bulletState == BULLET_EXPLOSION)
		_pAnimExplosion->Update(dt);
	else
		_pAnim->Update(dt);

	BaseObject::Update(dt);
}

void GunnerBullet::OnCollision(eSideCollision side)
{}

void GunnerBullet::OnCollision(BaseObject * obj)
{
	if (obj->GetObjectType() == ENEMY)
		return;

	_vx = 0;
	_vy = 0;
	_isDie = true;
	this->ChangeState(BULLET_EXPLOSION);
}

void GunnerBullet::Draw(Camera * camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (_isAllowDraw == false)
		return;

	switch (_bulletState)
	{
	case BULLET_EXPLOSION:
		_pAnimExplosion->SetPosition(this->GetPosition());
		if (camera)
			_pAnimExplosion->Draw(_pAnimExplosion->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		else
			_pAnimExplosion->Draw(_pAnimExplosion->GetPosition());
		break;

	default:
		_pAnim->SetReverse(_isReverse);
		_pAnim->SetPosition(this->GetPosition());

		if (camera)
			_pAnim->Draw(_pAnim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		else
			_pAnim->Draw(_pAnim->GetPosition());
		break;	
	}
}

void GunnerBullet::ChangeState(eBulletState state)
{
	_bulletState = state;

	switch (state)
	{
	case BULLET_EXPLOSION:
		_pAnimExplosion->SetAnimation(0, 8, 0.05, false);
		this->SetWidth(_pAnimExplosion->GetWidth());
		this->SetHeight(_pAnimExplosion->GetHeight());
		break;

	default:
		_pAnim->SetAnimation(0, 2);
		this->SetWidth(_pAnim->GetWidth());
		this->SetHeight(_pAnim->GetHeight());
		break;
	
	}
}
