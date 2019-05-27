#include "BangerBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"


BangerBullet::BangerBullet()
{
	_objectType = ENEMY_BULLET;
	_pAnim = new Animation(Define::NOTOR_BANGER_BULLET, 2, 3, 8, 8, D3DCOLOR_XRGB(0, 100, 100));
	_pAnimExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.1f);
	this->ChangeState(BULLET_FIRE);
	_HP = 3;
	_Damage = 2;
	_bulletY = 25.0f;
	_isAllowDraw = true;
}

BangerBullet::~BangerBullet()
{
	delete _pAnim;
	delete _pAnimExplosion;
}

RECT BangerBullet::GetBound()
{
	RECT r = RECT();

	switch (_bulletState)
	{

	case BULLET_EXPLOSION:
		r.left = _posX - 25;
		r.right = _posX + 25;
		r.top = _posY - 22;
		r.bottom = _posY + 23;
		break;

	case BULLET_FIRE:
		r.left = _posX - 4;
		r.top = _posY - 4;
		r.right = _posX + 4;
		r.bottom = _posY + 4;
		break;

	default: break;
	}

	return r;
}

void BangerBullet::NewEntity()
{
	_objectType = ENEMY_BULLET;
	_vy = -450;
	if (_isReverse == true)
	{
		//vx = 70;
		_vx = 100;

	}
	else
	{
		//vx = -70;
		_vx = -100;

	}
	ChangeState(BULLET_FIRE);
	_isDie = false;
	_isAllowDraw = true;
}

void BangerBullet::Update(float dt)
{
	if (_isAllowDraw == false)
		return;

	if (_isDie == false)
	{
		_vy += _bulletY;
		if (_vy > 300)
			_vy = 300;

	}
	else if (_pAnim->GetPause() == true || _pAnimExplosion->GetPause() == true)// da chay xong animation no
		_isAllowDraw = false;

	if (_bulletState == BULLET_EXPLOSION)
		_pAnimExplosion->Update(dt);
	else
		_pAnim->Update(dt);

	BaseObject::Update(dt);
}

void BangerBullet::OnCollision(eSideCollision side)
{}

void BangerBullet::OnCollision(BaseObject * obj)
{
	if (obj->GetObjectType() == ENEMY)
		return;
	_vx = 0;
	_vy = 0;
	_isDie = true;
	ChangeState(BULLET_EXPLOSION);
}

void BangerBullet::ChangeState(eBulletState state)
{
	_bulletState = state;

	switch (state)
	{
	case BULLET_EXPLOSION:
		_pAnimExplosion->SetAnimation(0, 8, 0.05, false);
		this->SetWidth(_pAnimExplosion->GetWidth());
		this->SetHeight(_pAnimExplosion->GetHeight());
		break;

	case BULLET_FIRE:
		_pAnim->SetAnimation(0, 1);
		this->SetWidth(_pAnim->GetWidth());
		this->SetHeight(_pAnim->GetHeight());
		break;

	default: break;
	}
}