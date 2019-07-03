#include "BlastBullet.h"
#include "../../../GameComponents/Camera.h"

BlastBullet::BlastBullet()
{
	_objectType = eObject_Enemy_Bullet;
	_isReverse = true;
	_Damage = 3;
	_MaxHP = 4;
	_HP = _MaxHP;

	BlastBullet::setState(eEnemyBullet_Fire);
}

BlastBullet::~BlastBullet()
{
	delete _pAnim;
}

RECT BlastBullet::getBound()
{
	RECT bound;
	bound.left = _posX - _width / 2;
	bound.top = _posY - _height / 2;
	bound.right = bound.left + _width;
	bound.bottom = bound.top + _height;
	return bound;
}

void BlastBullet::newObject()
{
	if (!_isReverse)
	{
		setReverse(true);
		setVx(-80.0f);
	}
	else
	{
		setReverse(false);
		setVx(80.0f);
	}

	_isAllowDraw = true;
	setState(eEnemyBullet_Fire);
}

void BlastBullet::update(float dt)
{
	if (_isAllowDraw)
	{
		_pAnim->update(dt);
		BaseObject::update(dt);
	}
}

void BlastBullet::onCollision(Side_Collision side)
{
	_vx = 0.0f;
	_vy = 0.0f;
	setState(eEnemyBullet_Explosion);
}

void BlastBullet::onCollision(BaseObject* obj)
{
	onCollision(eSide_None);
}

void BlastBullet::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (_isAllowDraw)
	{
		_pAnim->setPosition(getPosition());
		_pAnim->setReverse(_isReverse);
		if (camera)
			_pAnim->draw(_pAnim->getPosition(), rect, scale, camera->getTrans(), 0, rotationCenter, color);
		else
			_pAnim->draw(_pAnim->getPosition());
	}
}

void BlastBullet::setState(EnemyBullet_State state)
{
	_bulletState = state;

	switch (state)
	{
		case eEnemyBullet_Explosion:
			_pAnim = new Animation(Define::EXPLOSION_BLAST_HORNET, 1, 6, 34, 34, 0.05f, D3DCOLOR_XRGB(6, 113, 158));
			_pAnim->setAnimation(0, 6, 0.05f, false);
			break;

		case eEnemyBullet_Fire:
			_pAnim = new Animation(Define::BULLET_BLAST_HORNET, 1, 3, 24, 22, 0.05f, D3DCOLOR_XRGB(6, 113, 158));
			_pAnim->setAnimation(0, 3);
			break;

		default:
			break;
	}

	_width = _pAnim->getWidth();
	_height = _pAnim->getHeight();

}
