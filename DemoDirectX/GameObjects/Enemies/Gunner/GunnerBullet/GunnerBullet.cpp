#include "GunnerBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"

GunnerBullet::GunnerBullet()
{
	_objectType = Enumerator::Object_Type::ENEMY_BULLET;
	_pAnim = new Animation(Define::HEAD_GUNNER_BULLET, 1, 2, 23, 7, 0.1f);
	_pAnimExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.1f);
	_pCurrentAnim = nullptr;
	_isReverse = true;
	_HP = 3;
	_Damage = 3;
	_bulletX = 25.0f;
	_timeFire = 0.0f;
	_bulletState = Enumerator::EnemyBullet_State::FIRE;
	setState(Enumerator::EnemyBullet_State::FIRE);
}

GunnerBullet::~GunnerBullet()
{
	delete _pAnim;
	delete _pAnimExplosion;
}

RECT GunnerBullet::getBound()
{
	RECT bound;
	bound.left = _position.x - _width / 2;
	bound.top = _position.y - _height / 2;
	bound.right = bound.left + _width;
	bound.bottom = bound.top + _height;
	return bound;
}

void GunnerBullet::newObject()
{
	setReverse(_isReverse);
	float velocityX = (_isReverse) ? 80.0f : -80.0f;
	setVx(velocityX);

	float bulletX = (_isReverse) ? 25.0f : -25.0f;
	setBulletX(bulletX);

	_isDestroy = false;
	_isAllowDraw = true;
	setState(Enumerator::EnemyBullet_State::FIRE);
}

void GunnerBullet::update(float dt)
{
	if (!_isAllowDraw)
		return;

	if (!_isDestroy)
	{
		_velocity.x += _bulletX;
		if (_velocity.x > 300.0f)
			_velocity.x = 300.0f;
		else if (_velocity.x < -300.0f)
			_velocity.x = -300.0f;
	}
	else if (_pCurrentAnim->getPause())
		_isAllowDraw = false;

	_pCurrentAnim->update(dt);
	BaseObject::update(dt);
}

void GunnerBullet::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == Enumerator::Object_Type::ENEMY)
		return;

	_velocity.x = 0.0f;
	_velocity.y = 0.0f;
	_isDestroy = true;
	setState(Enumerator::EnemyBullet_State::EXPLOSION);
}

void GunnerBullet::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	_pCurrentAnim->setPosition(this->getPosition());
	_pCurrentAnim->setReverse(_isReverse);

	if (camera)
		_pCurrentAnim->draw(_pCurrentAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		_pCurrentAnim->draw(_pCurrentAnim->getPosition());
}

void GunnerBullet::changeAnimation(EnemyBullet_State state)
{
	switch (state)
	{
	case Enumerator::EnemyBullet_State::FIRE:
		_pCurrentAnim = _pAnim;
		_pCurrentAnim->setAnimation(0, 2);
		break;

	case Enumerator::EnemyBullet_State::EXPLOSION:
		_pCurrentAnim = _pAnimExplosion;
		_pCurrentAnim->setAnimation(0, 8, 0.05f, false);
		break;

	default:
		break;
	}

	_width = _pCurrentAnim->getWidth();
	_height = _pCurrentAnim->getHeight();
}

void GunnerBullet::setBulletX(float bulletX) { this->_bulletX = bulletX; }

void GunnerBullet::setState(EnemyBullet_State state)
{
	_bulletState = state;
	changeAnimation(state);
}
