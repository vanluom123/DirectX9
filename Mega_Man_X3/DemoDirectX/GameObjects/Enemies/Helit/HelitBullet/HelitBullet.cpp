#include "HelitBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"

HelitBullet::HelitBullet()
{
	_objectType = eObject_Enemy_Bullet;
	_HP = 3;
	_Damage = 2;
	_isReverse = false;
	_isDie = false;
	_isAllowDraw = true;
	_bulletX = 25.0f;
	_pAnim = new Animation(Define::HELIT_BULLET, 1, 1, 15, 10);
	_pAnimExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	_pCurrentAnim = nullptr;
	setState(eEnemyBullet_Fire);
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

	_isDie = false;
	_isAllowDraw = true;
	setState(eEnemyBullet_Fire);
}

RECT HelitBullet::getBound()
{
	RECT bound;

	if (_bulletState == eEnemyBullet_Fire)
	{
		bound.left = _posX - 7;
		bound.right = _posX + 8;
		bound.top = _posY - 5;
		bound.bottom = _posY + 5;

		return bound;
	}

	bound.left = _posX - 25;
	bound.right = _posX + 25;
	bound.top = _posY - 22;
	bound.bottom = _posY + 23;

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
		_pCurrentAnim->setPosition(this->getPosition());
		_pCurrentAnim->setReverse(_isReverse);
		if (camera)
			_pCurrentAnim->draw(_pCurrentAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			_pCurrentAnim->draw(_pCurrentAnim->getPosition());
	}
}

void HelitBullet::setState(EnemyBullet_State state)
{
	_bulletState = state;
	changeAnimation(state);
}

void HelitBullet::changeAnimation(EnemyBullet_State state)
{
	switch (state)
	{
		case eEnemyBullet_Fire:
		{
			_pCurrentAnim = _pAnim;
			_pCurrentAnim->setAnimation(0, 1);
			break;
		}

		case eEnemyBullet_Explosion:
		{
			_pCurrentAnim = _pAnimExplosion;
			_pCurrentAnim->setAnimation(0, 8, 0.05f, false);
			break;
		}

		default: break;
	}

	_width = _pCurrentAnim->getWidth();
	_height = _pCurrentAnim->getHeight();
}