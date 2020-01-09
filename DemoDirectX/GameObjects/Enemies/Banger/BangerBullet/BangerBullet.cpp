#include "BangerBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"


BangerBullet::BangerBullet()
{
	_objectType = Enumerator::Object_Type::ENEMY_BULLET;
	_HP = 3;
	_Damage = 2;
	_bulletY = 25.0f;
	_isAllowDraw = true;
	_pAnim = new Animation(Define::NOTOR_BANGER_BULLET, 2, 3, 8, 8, D3DCOLOR_XRGB(0, 100, 100));
	_pAnimExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.1f);
	_pCurrentAnim = nullptr;
	setState(Enumerator::EnemyBullet_State::FIRE);
}

BangerBullet::~BangerBullet()
{
	delete _pAnim;
	delete _pAnimExplosion;
}

RECT BangerBullet::getBound()
{
	RECT bound;
	bound.left = _posX - _width / 2;
	bound.top = _posY - _height / 2;
	bound.right = bound.left + _width;
	bound.bottom = bound.top + _height;
	return bound;
}

void BangerBullet::newObject()
{
	_objectType = Enumerator::Object_Type::ENEMY_BULLET;
	_vy = -450.0f;
	_vx = _isReverse ? 100.0f : -100.0f;
	_isDestroy = false;
	_isAllowDraw = true;
	setState(Enumerator::EnemyBullet_State::FIRE);
}

void BangerBullet::update(float dt)
{
	if (!_isAllowDraw)
		return;

	if (!_isDestroy)
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

void BangerBullet::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == Enumerator::Object_Type::ENEMY)
		return;
	_vx = 0.0f;
	_vy = 0.0f;
	_isDestroy = true;
	setState(Enumerator::EnemyBullet_State::EXPLOSION);
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
	case Enumerator::EnemyBullet_State::EXPLOSION:
		_pCurrentAnim = _pAnimExplosion;
		_pCurrentAnim->setAnimation(0, 8, 0.05f, false);
		break;

	case Enumerator::EnemyBullet_State::FIRE:
		_pCurrentAnim = _pAnim;
		_pAnim->setAnimation(0, 1);
		break;

	default: break;
	}

	_width = _pCurrentAnim->getWidth();
	_height = _pCurrentAnim->getHeight();
}
