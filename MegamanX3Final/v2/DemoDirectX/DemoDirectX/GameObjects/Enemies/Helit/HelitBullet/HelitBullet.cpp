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
	this->setState(BULLET_FIRE);

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
	if (_isReverse == true)
	{
		setReverse(true);
		setVx(80);
		SetBulletX(25.0f);
	}
	else
	{
		setReverse(false);
		setVx(-80);
		SetBulletX(-25.0f);
	}

	this->setState(BULLET_FIRE);
	_isDie = false;
	_isAllowDraw = true;
}

RECT HelitBullet::getBound()
{
	RECT bound = RECT();

	switch (_bulletState)
	{
		case BULLET_FIRE:
			{
				bound.left = _posX - 7;
				bound.right = _posX + 8;
				bound.top = _posY - 5;
				bound.bottom = _posY + 5;
				break;
			}

		case BULLET_EXPLOSION:
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
	else if (_pAnim->getPause() == true || _pAnimExplosion->getPause() == true)
		_isAllowDraw = false;

	if (_bulletState == BULLET_EXPLOSION)
		_pAnimExplosion->update(dt);
	else
		_pAnim->update(dt);

	BaseObject::update(dt);
}

void HelitBullet::onCollision(eSideCollision side)
{}

void HelitBullet::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == ENEMY)
		return;

	_vx = 0;
	_vy = 0;
	_isDie = true;
	this->setState(BULLET_EXPLOSION);
}

void HelitBullet::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (GameCollision::isCollision(camera->getBound(), getBound()) == false)
	{
		_isAllowDraw = false;
		_isDie = true;
	}

	if (_isAllowDraw == false)
		return;

	switch (_bulletState)
	{
		case BULLET_FIRE:
			{
				_pAnim->setReverse(_isReverse);
				_pAnim->setPosition(this->getPosition());
				if (camera)
					_pAnim->draw(_pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
				else
					_pAnim->draw(_pAnim->getPosition());
				break;
			}

		case BULLET_EXPLOSION:
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

void HelitBullet::setState(eBulletState state)
{
	_bulletState = state;

	switch (state)
	{
		case BULLET_FIRE:
			{
				_pAnim->setAnimation(0, 1);
				this->setWidth(_pAnim->getWidth());
				this->setHeight(_pAnim->getHeight());
				break;
			}

		case BULLET_EXPLOSION:
			{
				_pAnimExplosion->setAnimation(0, 8, 0.05f, false);
				this->setWidth(_pAnimExplosion->getWidth());
				this->setHeight(_pAnimExplosion->getHeight());
				break;
			}

		default: break;
	}
}
