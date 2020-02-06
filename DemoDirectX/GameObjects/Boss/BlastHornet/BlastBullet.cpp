#include "BlastBullet.h"
#include "../../../GameComponents/Camera.h"
#include "../../Player/PlayerBullet/PlayerBullet.h"
#include "../../../GameComponents/GameCollision.h"

BlastBullet::BlastBullet() : _timeDelay(0.0f)
{
	BlastBullet::loadSprite();
	_objectType = Enumerator::Object_Type::ENEMY_BULLET;
	_isReverse = true;
	_Damage = 3;
	_MaxHP = 4;
	_HP = _MaxHP;
	_pCurrentAnim = nullptr;
	BlastBullet::setState(Enumerator::EnemyBullet_State::FIRE);
}

void BlastBullet::loadSprite()
{
	_pAnim = new Animation(Define::BULLET_BLAST_HORNET, 1, 3, 24, 22, 0.05f, D3DCOLOR_XRGB(6, 113, 158));
	_pAnimExplosion = new Animation(Define::EXPLOSION_BLAST_HORNET, 1, 6, 34, 34, 0.05f, D3DCOLOR_XRGB(6, 113, 158));
}

BlastBullet::~BlastBullet()
{
	delete _pAnim;
	delete _pAnimExplosion;
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
	loadSprite();

	if (!_isReverse)
	{
		setReverse(true);
		setVx(-80.0f);
		setVy(50.0f);
	}
	else
	{
		setReverse(false);
		setVx(80.0f);
		setVy(50.0f);
	}

	_timeDelay = 0.0f;
	_isDestroy = false;
	_isAllowDraw = true;
	setState(Enumerator::EnemyBullet_State::FIRE);
}

void BlastBullet::update(float dt)
{
	_timeDelay += dt;

	m_towardsPlayer.x = Player::getInstance()->getPosition().x - getPosition().x;
	m_towardsPlayer.y = Player::getInstance()->getPosition().y - getPosition().y;
	D3DXVec2Normalize(&m_towardsPlayer, &m_towardsPlayer);

	_vx = m_towardsPlayer.x * 125.0f;
	_vy = m_towardsPlayer.y * 125.0f;

	if (_isAllowDraw)
	{
		if (_pCurrentAnim->getPause() && _isDestroy)
			_isAllowDraw = false;

		_pCurrentAnim->update(dt);
		BaseObject::update(dt);
	}
}

void BlastBullet::onCollision(Side_Collision side)
{
	_vx = 0.0f;
	_vy = 0.0f;
}

void BlastBullet::onCollision(BaseObject * obj)
{
	_vx = 0.0f;
	_vy = 0.0f;

	if (_isDestroy) return;

	if (obj->getObjectType() == Enumerator::Object_Type::ROCKMAN_BULLET)
	{
		_isDestroy = true;
		setState(Enumerator::EnemyBullet_State::EXPLOSION);
	}
	else if (obj->getObjectType() == Enumerator::Object_Type::ROCKMAN)
	{
		_isDestroy = true;
		setState(Enumerator::EnemyBullet_State::EXPLOSION);
	}
	else
	{
		if (_timeDelay > 1.5f)
		{
			_timeDelay = 0.0f;
			_isDestroy = true;
			setState(Enumerator::EnemyBullet_State::EXPLOSION);
		}
	}
}

void BlastBullet::draw(Camera * camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{
	if (_isAllowDraw)
	{
		_pCurrentAnim->setPosition(getPosition());
		_pCurrentAnim->setReverse(_isReverse);
		if (camera)
			_pCurrentAnim->draw(_pCurrentAnim->getPosition(), rect, scale, camera->getTrans(), 0, rotationCenter, color);
		else
			_pCurrentAnim->draw(_pCurrentAnim->getPosition());
	}
}

void BlastBullet::setState(EnemyBullet_State state)
{
	_bulletState = state;
	changeAnimation(state);
}

void BlastBullet::changeAnimation(EnemyBullet_State state)
{
	switch (state)
	{
		case Enumerator::EnemyBullet_State::EXPLOSION:
			_pCurrentAnim = _pAnimExplosion;
			_pCurrentAnim->setAnimation(0, 6, 0.05f, false);
			break;

		case Enumerator::EnemyBullet_State::FIRE:
			_pCurrentAnim = _pAnim;
			_pCurrentAnim->setAnimation(0, 3);
			break;

		default:
			break;
	}

	_width = _pCurrentAnim->getWidth();
	_height = _pCurrentAnim->getHeight();
}