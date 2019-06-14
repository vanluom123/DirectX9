#include "GunnerBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"

GunnerBullet::GunnerBullet()
{
	_objectType = ENEMY_BULLET;
	_pAnim = new Animation(Define::HEAD_GUNNER_BULLET, 1, 2, 23, 7, 0.1f);
	_pAnimExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.1f);

	_isReverse = true;
	_HP = 3;
	_Damage = 3;
	_bulletX = 25.0f;
	_timeFire = 0.0f;

	this->setState(BULLET_FIRE);
}

GunnerBullet::~GunnerBullet()
{
	delete _pAnim;
	delete _pAnimExplosion;
}

RECT GunnerBullet::getBound()
{
	RECT bound = RECT();

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

void GunnerBullet::newObject()
{
	if (!_isReverse)
	{
		setReverse(false);
		setVx(-80.0f);
		SetBulletX(-25.0f);
	}
	else
	{
		setReverse(true);
		setVx(80.0f);
		SetBulletX(25.0f);
	}

	this->setState(BULLET_FIRE);
	_isDie = false;
	_isAllowDraw = true;
}

void GunnerBullet::update(float dt)
{
	if (_isAllowDraw)
	{
		if (!_isDie)
		{
			_vx += _bulletX;
			if (_vx > 300)
				_vx = 300;
			else if (_vx < -300)
				_vx = -300;
		}
		else if (_pAnim->getPause() || _pAnimExplosion->getPause())
			_isAllowDraw = false;

		if (_bulletState == BULLET_EXPLOSION)
			_pAnimExplosion->update(dt);
		else
			_pAnim->update(dt);

		BaseObject::update(dt);
	}
}

void GunnerBullet::onCollision(eSideCollision side)
{}

void GunnerBullet::onCollision(BaseObject * obj)
{
	if (obj->getObjectType() == ENEMY)
		return;

	_vx = 0.0f;
	_vy = 0.0f;
	_isDie = true;
	this->setState(BULLET_EXPLOSION);
}

void GunnerBullet::draw(Camera * camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (_isAllowDraw)
	{
		switch (_bulletState)
		{
		case BULLET_EXPLOSION:
		{
			_pAnimExplosion->setPosition(this->getPosition());
			if (camera)
				_pAnimExplosion->draw(_pAnimExplosion->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
			else
				_pAnimExplosion->draw(_pAnimExplosion->getPosition());
			break;
		}

		default:
		{
			_pAnim->setReverse(_isReverse);
			_pAnim->setPosition(this->getPosition());

			if (camera)
				_pAnim->draw(_pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
			else
				_pAnim->draw(_pAnim->getPosition());
			break;
		}
		}
	}
}

void GunnerBullet::setState(eBulletState state)
{
	_bulletState = state;

	switch (state)
	{
	case BULLET_EXPLOSION:
	{
		_pAnimExplosion->setAnimation(0, 8, 0.05f, false);
		this->setWidth(_pAnimExplosion->getWidth());
		this->setHeight(_pAnimExplosion->getHeight());
		break;
	}

	default:
	{
		_pAnim->setAnimation(0, 2);
		this->setWidth(_pAnim->getWidth());
		this->setHeight(_pAnim->getHeight());
		break;
	}
	
	}
}
