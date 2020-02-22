#include "HelitBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"

HelitBullet::HelitBullet()
{
	_objectType = Enumerator::Object_Type::ENEMY_BULLET;
	_HP = 3;
	_Damage = 2;
	_isReverse = false;
	_isDestroy = false;
	_isAllowDraw = true;
	_bulletX = 25.0f;
	_pAnim = new Animation(Define::HELIT_BULLET, 1, 1, 15, 10);
	_pAnimExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30);
	_pCurrentAnim = nullptr;
	HelitBullet::setState(Enumerator::EnemyBullet_State::FIRE);
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

	_isDestroy = false;
	_isAllowDraw = true;
	setState(Enumerator::EnemyBullet_State::FIRE);
}

RECT HelitBullet::getBound()
{
	RECT bound;
	bound.left = _position.x - _width / 2;
	bound.top = _position.y - _height / 2;
	bound.right = bound.left + _width;
	bound.bottom = bound.top + _height;
	return bound;
}

void HelitBullet::update(float dt)
{
	if (!_isAllowDraw)
		return;

	if (!_isDestroy)
	{
		_velocity.x += _bulletX;
		if (_velocity.x > 300)
			_velocity.x = 300;
		else if (_velocity.x < -300)
			_velocity.x = -300;
	}
	else if (_pAnim->getPause() || _pAnimExplosion->getPause())
		_isAllowDraw = false;

	if (_bulletState == Enumerator::EnemyBullet_State::EXPLOSION)
		_pAnimExplosion->update(dt);
	else
		_pAnim->update(dt);

	BaseObject::update(dt);
}

void HelitBullet::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == Enumerator::Object_Type::ENEMY)
		return;

	_velocity.x = 0.0f;
	_velocity.y = 0.0f;
	_isDestroy = true;
	setState(Enumerator::EnemyBullet_State::EXPLOSION);
}

void HelitBullet::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (!GameCollision::getInstance()->AABBCheck(camera->getBound(), getBound()))
	{
		_isAllowDraw = false;
		_isDestroy = true;
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
	case Enumerator::EnemyBullet_State::FIRE:
	{
		_pCurrentAnim = _pAnim;
		_pCurrentAnim->setAnimation(0, 1);
		break;
	}

	case Enumerator::EnemyBullet_State::EXPLOSION:
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