#include "HelitBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"

HelitBullet::HelitBullet()
{
	_objectType = eObject_Enemy_Bullet;
	_pAnim = new Animation(Define::HELIT_BULLET, 1, 1, 15, 10);
	_pAnimExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	_HP = 3;
	_Damage = 2;
	setState(eEnemyBullet_Fire);

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

void HelitBullet::newObject()
{
	if (_isReverse)
	{
		setReverse(true);
		setVx(80.0f);
		setBulletX(25.0f);
	}
	else
	{
		setReverse(false);
		setVx(-80.0f);
		setBulletX(-25.0f);
	}

	setState(eEnemyBullet_Fire);
	_isDie = false;
	_isAllowDraw = true;
}

RECT HelitBullet::getBound()
{
	RECT bound = RECT();

	switch (_bulletState)
	{
		case eEnemyBullet_Fire:
		{
			bound.left = _posX - 7;
			bound.right = _posX + 8;
			bound.top = _posY - 5;
			bound.bottom = _posY + 5;
			break;
		}

		case eEnemyBullet_Explosion:
		{
			bound.left = _posX - 25;
			bound.right = _posX + 25;
			bound.top = _posY - 22;
			bound.bottom = _posY + 23;
			break;
		}

		default: break;

	}

	return bound;
}

void HelitBullet::update(float dt)
{
	if (!_isAllowDraw)
		return;

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

	if (_bulletState == eEnemyBullet_Explosion)
		_pAnimExplosion->update(dt);
	else
		_pAnim->update(dt);

	BaseObject::update(dt);
}

void HelitBullet::onCollision(Side_Collision side)
{}

void HelitBullet::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == eObject_Enemy)
		return;

	_vx = 0.0f;
	_vy = 0.0f;
	_isDie = true;
	setState(eEnemyBullet_Explosion);
}

void HelitBullet::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (!GameCollision::isCollision(camera->getBound(), getBound()))
	{
		_isAllowDraw = false;
		_isDie = true;
	}

	if (_isAllowDraw)
	{
		switch (_bulletState)
		{
			case eEnemyBullet_Fire:
			{
				_pAnim->setReverse(_isReverse);
				_pAnim->setPosition(this->getPosition());
				if (camera)
					_pAnim->draw(_pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
				else
					_pAnim->draw(_pAnim->getPosition());
				break;
			}

			case eEnemyBullet_Explosion:
			{
				_pAnimExplosion->setPosition(this->getPosition());
				if (camera)
					_pAnimExplosion->draw(_pAnimExplosion->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
				else
					_pAnimExplosion->draw(_pAnimExplosion->getPosition());
				break;
			}

			default: break;
		}
	}
}

void HelitBullet::setState(EnemyBullet_State state)
{
	_bulletState = state;

	switch (state)
	{
		case eEnemyBullet_Fire:
		{
			_pAnim->setAnimation(0, 1);
			setWidth(_pAnim->getWidth());
			setHeight(_pAnim->getHeight());
			break;
		}

		case eEnemyBullet_Explosion:
		{
			_pAnimExplosion->setAnimation(0, 8, 0.05f, false);
			setWidth(_pAnimExplosion->getWidth());
			setHeight(_pAnimExplosion->getHeight());
			break;
		}

		default: break;
	}
}
