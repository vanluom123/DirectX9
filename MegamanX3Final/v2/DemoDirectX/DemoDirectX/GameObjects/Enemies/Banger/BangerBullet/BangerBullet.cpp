#include "BangerBullet.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../../../../GameComponents/Camera.h"
#include "../../../../GameComponents/GameCollision.h"


BangerBullet::BangerBullet()
{
	_objectType = ENEMY_BULLET;
	_pAnim = new Animation(Define::NOTOR_BANGER_BULLET, 2, 3, 8, 8, D3DCOLOR_XRGB(0, 100, 100));
	_pAnimExplosion = new Animation(Define::EXPLOSIONS, 1, 8, 35, 30, 0.1f);
	this->setState(BULLET_FIRE);
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
	RECT bound;

	switch (_bulletState)
	{

	case BULLET_EXPLOSION:
		bound.left = _posX - 25;
		bound.right = _posX + 25;
		bound.top = _posY - 22;
		bound.bottom = _posY + 23;
		break;

	case BULLET_FIRE:
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
	_objectType = ENEMY_BULLET;
	_vy = -450;
	if (_isReverse == true)
	{
		//vx = 70;
		_vx = 100;

	}
	else
	{
		//vx = -70;
		_vx = -100;

	}
	setState(BULLET_FIRE);
	_isDie = false;
	_isAllowDraw = true;
}

void BangerBullet::update(float dt)
{
	if (_isAllowDraw == false)
		return;

	if (_isDie == false)
	{
		_vy += _bulletY;
		if (_vy > 300)
			_vy = 300;

	}
	else if (_pAnim->getPause() == true || _pAnimExplosion->getPause() == true)// da chay xong animation no
		_isAllowDraw = false;

	if (_bulletState == BULLET_EXPLOSION)
		_pAnimExplosion->update(dt);
	else
		_pAnim->update(dt);

	BaseObject::update(dt);
}

void BangerBullet::onCollision(eSideCollision side)
{}

void BangerBullet::onCollision(BaseObject * obj)
{
	if (obj->getObjectType() == ENEMY)
		return;
	_vx = 0;
	_vy = 0;
	_isDie = true;
	setState(BULLET_EXPLOSION);
}

void BangerBullet::setState(eBulletState state)
{
	_bulletState = state;

	switch (state)
	{
	case BULLET_EXPLOSION:
		_pAnimExplosion->setAnimation(0, 8, 0.05, false);
		this->setWidth(_pAnimExplosion->getWidth());
		this->setHeight(_pAnimExplosion->getHeight());
		break;

	case BULLET_FIRE:
		_pAnim->setAnimation(0, 1);
		this->setWidth(_pAnim->getWidth());
		this->setHeight(_pAnim->getHeight());
		break;

	default: break;
	}
}