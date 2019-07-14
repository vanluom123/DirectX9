#include "GunnerBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"

GunnerBullet::GunnerBullet()
{
	_objectType = eObject_Enemy_Bullet;
	_pAnim = new Animation(Define::HEAD_GUNNER_BULLET, 1, 2, 23, 7, 0.1f);
	_pAnimExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.1f);
	_pCurrentAnim = nullptr;
	_isReverse = true;
	_HP = 3;
	_Damage = 3;
	_bulletX = 25.0f;
	_timeFire = 0.0f;
	_bulletState = eEnemyBullet_Fire;
	setState(eEnemyBullet_Fire);
}

GunnerBullet::~GunnerBullet()
{
	delete _pAnim;
	delete _pAnimExplosion;
}

RECT GunnerBullet::getBound()
{
	RECT bound;

	if (_bulletState == eEnemyBullet_Fire) {
		bound.left = _posX - 10;
		bound.right = _posX + 13;
		bound.top = _posY - 3;
		bound.bottom = _posY + 4;

		return bound;
	}

	bound.left = _posX - 25;
	bound.right = _posX + 25;
	bound.top = _posY - 22;
	bound.bottom = _posY + 23;

	return bound;
}

void GunnerBullet::newObject()
{
	if (!_isReverse)
	{
		setReverse(false);
		setVx(-80.0f);
		setBulletX(-25.0f);
	}
	else
	{
		setReverse(true);
		setVx(80.0f);
		setBulletX(25.0f);
	}

	_isDie = false;
	_isAllowDraw = true;
	this->setState(eEnemyBullet_Fire);
}

void GunnerBullet::update(float dt)
{
	if (_isAllowDraw)
	{
		if (!_isDie)
		{
			_vx += _bulletX;
			if (_vx > 300.0f)
				_vx = 300.0f;
			else if (_vx < -300.0f)
				_vx = -300.0f;
		}
		else if (_pCurrentAnim->getPause())
			_isAllowDraw = false;

		_pCurrentAnim->update(dt);
		BaseObject::update(dt);
	}
}

void GunnerBullet::onCollision(Side_Collision side)
{}

void GunnerBullet::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == eObject_Enemy)
		return;

	_vx = 0.0f;
	_vy = 0.0f;
	_isDie = true;
	this->setState(eEnemyBullet_Explosion);
}

void GunnerBullet::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{
	if (_isAllowDraw)
	{
		_pCurrentAnim->setPosition(this->getPosition());
		_pCurrentAnim->setReverse(_isReverse);
		if (camera)
			_pCurrentAnim->draw(_pCurrentAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			_pCurrentAnim->draw(_pCurrentAnim->getPosition());
	}
}

void GunnerBullet::changeAnimation(EnemyBullet_State state)
{
	switch (state)
	{
		case Enumerator::eEnemyBullet_Fire:
			_pCurrentAnim = _pAnim;
			_pCurrentAnim->setAnimation(0, 2);
			break;

		case Enumerator::eEnemyBullet_Explosion:
			_pCurrentAnim = _pAnimExplosion;
			_pCurrentAnim->setAnimation(0, 8, 0.05f, false);
			break;

		default:
			break;
	}

	_width = _pCurrentAnim->getWidth();
	_height = _pCurrentAnim->getHeight();
}

inline void GunnerBullet::setBulletX(float bulletX) { this->_bulletX = bulletX; }

void GunnerBullet::setState(EnemyBullet_State state)
{
	_bulletState = state;
	changeAnimation(state);
}
