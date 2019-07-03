#include "BangerBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"


BangerBullet::BangerBullet()
{
	_objectType = eObject_Enemy_Bullet;
	_pAnim = new Animation(Define::NOTOR_BANGER_BULLET, 2, 3, 8, 8, D3DCOLOR_XRGB(0, 100, 100));
	_pAnimExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.1f);
	BangerBullet::setState(eEnemyBullet_Fire);
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

RECT BangerBullet::getBound()
{
	RECT bound = {};

	switch (_bulletState)
	{

		case eEnemyBullet_Explosion:
			bound.left = _posX - 25;
			bound.right = _posX + 25;
			bound.top = _posY - 22;
			bound.bottom = _posY + 23;
			break;

		case eEnemyBullet_Fire:
			bound.left = _posX - 4;
			bound.top = _posY - 4;
			bound.right = _posX + 4;
			bound.bottom = _posY + 4;
			break;

		default:
			break;
	}

	return bound;
}

void BangerBullet::newObject()
{
	_objectType = eObject_Enemy_Bullet;
	_vy = -450.0f;
	if (_isReverse)
	{
		//vx = 70;
		_vx = 100.0f;

	}
	else
	{
		//vx = -70;
		_vx = -100.0f;

	}
	setState(eEnemyBullet_Fire);
	_isDie = false;
	_isAllowDraw = true;
}

void BangerBullet::update(float dt)
{
	if (!_isAllowDraw)
		return;

	if (!_isDie)
	{
		_vy += _bulletY;
		if (_vy > 300)
			_vy = 300;

	}
	else if (_pAnim->getPause() || _pAnimExplosion->getPause())// da chay xong animation no
		_isAllowDraw = false;

	if (_bulletState == eEnemyBullet_Explosion)
		_pAnimExplosion->update(dt);
	else
		_pAnim->update(dt);

	BaseObject::update(dt);
}

void BangerBullet::onCollision(Side_Collision side)
{}

void BangerBullet::onCollision(BaseObject * obj)
{
	if (obj->getObjectType() == eObject_Enemy)
		return;
	_vx = 0.0f;
	_vy = 0.0f;
	_isDie = true;
	setState(eEnemyBullet_Explosion);
}

void BangerBullet::setState(EnemyBullet_State state)
{
	_bulletState = state;

	switch (state)
	{
		case eEnemyBullet_Explosion:
			_pAnimExplosion->setAnimation(0, 8, 0.05f, false);
			setWidth(_pAnimExplosion->getWidth());
			setHeight(_pAnimExplosion->getHeight());
			break;

		case eEnemyBullet_Fire:
			_pAnim->setAnimation(0, 1);
			setWidth(_pAnim->getWidth());
			setHeight(_pAnim->getHeight());
			break;

		default: break;
	}
}