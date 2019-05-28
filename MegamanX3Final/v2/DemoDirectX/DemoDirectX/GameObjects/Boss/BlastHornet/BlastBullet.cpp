#include "BlastBullet.h"
#include "../../../GameComponents/Camera.h"

BlastBullet::BlastBullet()
{
	_objectType = eObjectType::ENEMY_BULLET;
	_isReverse = true;
	_Damage = 3;
	_MaxHP = 4;
	_HP = _MaxHP;

	this->ChangeState(eBulletState::BULLET_FIRE);
}

BlastBullet::~BlastBullet()
{
	delete _pAnim;
}

RECT BlastBullet::GetBound()
{
	RECT bound;
	bound.left = _posX - _width / 2;
	bound.top = _posY - _height / 2;
	bound.right = bound.left + _width;
	bound.bottom = bound.top + _height;
	return bound;
}

void BlastBullet::NewEntity()
{
	if (_isReverse == false)
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
	_isAllowDraw = true;
	ChangeState(eBulletState::BULLET_FIRE);
}

void BlastBullet::Update(float dt)
{
	if (_isAllowDraw == false)
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

	_pAnim->Update(dt);
	BaseObject::Update(dt);
}

void BlastBullet::OnCollision(eSideCollision side)
{
	_vx = 0;
	_vy = 0;
	//isBurst = true;
	ChangeState(eBulletState::BULLET_EXPLOSION);
}

void BlastBullet::OnCollision(BaseObject* obj)
{
	OnCollision(eSideCollision::NONE);
}

void BlastBullet::Draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (_isAllowDraw == false)
		return;

	_pAnim->SetPosition(GetPosition());
	_pAnim->SetReverse(_isReverse);
	if (camera)
		_pAnim->Draw(GetPosition(), rect, scale, camera->GetTrans(), 0, rotationCenter, color);
	else
		_pAnim->Draw(GetPosition());
}

void BlastBullet::ChangeState(eBulletState state)
{
	switch (state)
	{
	case BULLET_EXPLOSION:
		_pAnim = new Animation("Resources/Enemies/BlastHornet/Burst/BurstAnimation.png", 1, 6, 34, 34, 0.05, D3DCOLOR_XRGB(6, 113, 158));
		_pAnim->SetAnimation(0, 6, 0.05, false);
		break;

	case BULLET_FIRE:
		_pAnim = new Animation("Resources/Enemies/BlastHornet/Bullet/BulletAnim.png", 1, 3, 24, 22, 0.05, D3DCOLOR_XRGB(6, 113, 158));
		_pAnim->SetAnimation(0, 3);
		break;

	default:break;
	}

	_width = _pAnim->GetWidth();
	_height = _pAnim->GetHeight();

	_bulletState = state;
}
