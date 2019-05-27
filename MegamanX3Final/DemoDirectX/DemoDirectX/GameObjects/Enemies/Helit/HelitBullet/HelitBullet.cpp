#include "HelitBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"

HelitBullet::HelitBullet()
{
	_objectType = ENEMY_BULLET;
	_pAnim = new Animation(Define::HELIT_BULLET, 1, 1, 15, 10);
	_pAnimExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	_HP = 3;
	_Damage = 2;
	this->ChangeState(BULLET_FIRE);

	_isReverse = false;
	_isDie = false;
	_isAllowDraw = true;
	_bulletX = 25.0f;
}

HelitBullet::~HelitBullet()
{
	delete _pAnim;
	delete _pAnimExplosion;
}

void HelitBullet::NewEntity()
{
	if (_isReverse == true)
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
	_isDie = false;
	_isAllowDraw = true;
}

RECT HelitBullet::GetBound()
{
	RECT r = RECT();

	switch (_bulletState)
	{
	default:
	{
		r.left = _posX - 7;
		r.right = _posX + 8;
		r.top = _posY - 5;
		r.bottom = _posY + 5;
		break;
	}

	case BULLET_EXPLOSION:
	{
		r.left = _posX - 25;
		r.right = _posX + 25;
		r.top = _posY - 22;
		r.bottom = _posY + 23;
		break;
	}
	}

	return r;
}

void HelitBullet::Update(float dt)
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

void HelitBullet::OnCollision(eSideCollision side)
{}

void HelitBullet::OnCollision(BaseObject * obj)
{
	if (obj->GetObjectType() == ENEMY)
		return;

	_vx = 0;
	_vy = 0;
	_isDie = true;
	this->ChangeState(BULLET_EXPLOSION);
}

void HelitBullet::Draw(Camera * camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (GameCollision::IsCollision(camera->GetBound(), GetBound()) == false)
	{
		_isAllowDraw = false;
		_isDie = true;
	}

	if (_isAllowDraw == false)
		return;

	switch (_bulletState)
	{
	case BULLET_FIRE:
		_pAnim->SetReverse(_isReverse);
		_pAnim->SetPosition(this->GetPosition());
		if (camera)
			_pAnim->Draw(_pAnim->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		else
			_pAnim->Draw(_pAnim->GetPosition());
		break;

	case BULLET_EXPLOSION:
		_pAnimExplosion->SetPosition(this->GetPosition());
		if (camera)
			_pAnimExplosion->Draw(_pAnimExplosion->GetPosition(), rect, scale, camera->GetTrans(), angle, rotationCenter, color);
		else
			_pAnimExplosion->Draw(_pAnimExplosion->GetPosition());
		break;

	default: break;
	}
}

void HelitBullet::ChangeState(eBulletState state)
{
	_bulletState = state;

	switch (state)
	{
	case BULLET_FIRE:
		_pAnim->SetAnimation(0, 1);
		this->SetWidth(_pAnim->GetWidth());
		this->SetHeight(_pAnim->GetHeight());
		break;

	case BULLET_EXPLOSION:
		_pAnimExplosion->SetAnimation(0, 8, 0.05f, false);
		this->SetWidth(_pAnimExplosion->GetWidth());
		this->SetHeight(_pAnimExplosion->GetHeight());
		break;

	default: break;
	}
}
