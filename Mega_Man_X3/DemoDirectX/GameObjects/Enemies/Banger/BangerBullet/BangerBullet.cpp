#include "BangerBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"


BangerBullet::BangerBullet()
{
	_objectType = eObject_Enemy_Bullet;
	_HP = 3;
	_Damage = 2;
	_bulletY = 25.0f;
	_isAllowDraw = true;
	_pAnim = new Animation(Define::NOTOR_BANGER_BULLET, 2, 3, 8, 8, D3DCOLOR_XRGB(0, 100, 100));
	_pAnimExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.1f);
	_pCurrentAnim = nullptr;
	setState(eEnemyBullet_Fire);
}

BangerBullet::~BangerBullet()
{
	delete _pAnim;
	delete _pAnimExplosion;
}

RECT BangerBullet::getBound()
{
	RECT bound;

	if (_bulletState == eEnemyBullet_Fire)
	{
		bound.left = _posX - 4;
		bound.top = _posY - 4;
		bound.right = _posX + 4;
		bound.bottom = _posY + 4;

		return bound;
	}

	bound.left = _posX - 25;
	bound.top = _posY - 22;
	bound.right = _posX + 25;
	bound.bottom = _posY + 23;

	return bound;
}

void BangerBullet::newObject()
{
	_objectType = eObject_Enemy_Bullet;
	_vy = -450.0f;
	_vx = _isReverse ? 100.0f : -100.0f;
	_isDie = false;
	_isAllowDraw = true;
	setState(eEnemyBullet_Fire);
}

void BangerBullet::update(float dt)
{
	if (!_isAllowDraw)
		return;

	if (!_isDie)
	{
		_vy += _bulletY;
		if (_vy > 300.0f)
			_vy = 300.0f;
	}
	else if (_pCurrentAnim->getPause()) // The last explosion frame
		_isAllowDraw = false;

	_pCurrentAnim->update(dt);
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
	changeAnimation(state);
}

void BangerBullet::changeAnimation(EnemyBullet_State state)
{
	switch (state)
	{
		case eEnemyBullet_Explosion:
			_pCurrentAnim = _pAnimExplosion;
			_pCurrentAnim->setAnimation(0, 8, 0.05f, false);
			break;

		case eEnemyBullet_Fire:
			_pCurrentAnim = _pAnim;
			_pAnim->setAnimation(0, 1);
			break;

		default: break;
	}

	_width = _pCurrentAnim->getWidth();
	_height = _pCurrentAnim->getHeight();
}
