#include "PlayerBullet.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"

PlayerBullet::PlayerBullet() :
	m_pBullet(nullptr), m_pBulletLevel1(nullptr),
	m_pBulletLevel2(nullptr), m_pExplosion(nullptr),
	m_pExplosionLevel1(nullptr), m_pExplosionLevel2(nullptr),
	m_pCurrentAnimation(nullptr)
{
	loadSprite();
	_objectType = eObject_RockMan_Bullet;
	_bulletX = 25.0f;
	_isExplosion = false;
	_bulletType = ePlayerBullet_Type_Normal;
	_bulletState = ePlayerBullet_Fire;
	changeBullet(_bulletState, _bulletType);
}

PlayerBullet::~PlayerBullet()
{
	delete m_pBullet;
	delete m_pBulletLevel1;
	delete m_pBulletLevel2;
	delete m_pExplosion;
	delete m_pExplosionLevel1;
	delete m_pExplosionLevel2;
}

bool PlayerBullet::getExplosion() const
{
	return _isExplosion;
}

void PlayerBullet::setBulletX(float bulletX)
{
	this->_bulletX = bulletX;
}

PlayerBullet_Type PlayerBullet::getPlayerBulletType() const
{
	return _bulletType;
}

void PlayerBullet::newBullet(float bx, float by, bool direction, PlayerBullet_Type type)
{
	loadSprite();
	_posX = bx;
	_posY = by;
	_isAllowDraw = true;
	_isExplosion = false;
	_bulletState = ePlayerBullet_Fire;
	_bulletType = type;

	setReverse(direction);
	_vx = (direction) ? -300.0f : 300.0f;

	changeBullet(_bulletState, type);
}

void PlayerBullet::changeBullet(PlayerBullet_State state, PlayerBullet_Type type)
{
	switch (state)
	{
		case ePlayerBullet_Fire:
		{
			switch (type)
			{
				case ePlayerBullet_Type_Normal:
					_Damage = 1;
					m_pCurrentAnimation = m_pBullet;
					break;

				case ePlayerBullet_Type_First_Level:
					_Damage = 2;
					m_pCurrentAnimation = m_pBulletLevel1;
					break;

				case ePlayerBullet_Type_Second_Level:
					_Damage = 4;
					m_pCurrentAnimation = m_pBulletLevel2;
					break;

				default: break;
			}
		}
		case ePlayerBullet_Explosion:
		{
			switch (type)
			{
				case ePlayerBullet_Type_Explosion_Normal:
					m_pCurrentAnimation = m_pExplosion;
					m_pCurrentAnimation->setLoop(false);
					break;

				case ePlayerBullet_Type_Explosion_First_Level:
				{
					m_pCurrentAnimation = m_pExplosionLevel1;
					m_pCurrentAnimation->setLoop(false);

					m_pCurrentAnimation->isAnchorPoint(true);
					if (_isReverse)
						m_pCurrentAnimation->setAnchorPoint(1.0f, 1.0f);
					else
						m_pCurrentAnimation->setAnchorPoint(1.0f, 1.0f);

					break;
				}

				case ePlayerBullet_Type_Explosion_Second_Level:
					m_pCurrentAnimation = m_pExplosionLevel2;
					m_pCurrentAnimation->setLoop(false);
					break;

				default: break;
			}
		}

		default: break;
	}

	_width = m_pCurrentAnimation->getWidth();
	_height = m_pCurrentAnimation->getHeight();
}

RECT PlayerBullet::getBound()
{
	RECT bound;
	bound.left = _posX - _width / 2;
	bound.top = _posY - _height / 2;
	bound.right = bound.left + _width;
	bound.bottom = bound.top + _height;
	return bound;
}

void PlayerBullet::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (!GameCollision::isCollision(getBound(), camera->getBound()))
	{
		_isAllowDraw = false;
		_isExplosion = true;
	}

	if (_isAllowDraw)
	{
		m_pCurrentAnimation->setReverse(_isReverse);
		m_pCurrentAnimation->setPosition(this->getPosition());

		if (camera)
			m_pCurrentAnimation->draw(this->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			m_pCurrentAnimation->draw(this->getPosition());
	}
}

void PlayerBullet::update(float dt)
{
	if (_isAllowDraw)
	{
		if (m_pCurrentAnimation->getPause())
			_isAllowDraw = false;

		BaseObject::update(dt);
		m_pCurrentAnimation->update(dt);
	}
}

void PlayerBullet::onCollision(Side_Collision side)
{
	// Do nothing
}

void PlayerBullet::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() != eObject_Enemy
		&& obj->getObjectType() != eObject_Boss
		&& obj->getObjectType() != eObject_Box)
		return;

	if (obj->getHP() <= 0)
		return;

	_vx = 0.0f;
	_vx = 0.0f;
	_isExplosion = true;
	_bulletState = ePlayerBullet_Explosion;

	switch (_bulletType)
	{
		case ePlayerBullet_Type_Normal:
			_bulletType = ePlayerBullet_Type_Explosion_Normal;
			break;

		case ePlayerBullet_Type_First_Level:
			_bulletType = ePlayerBullet_Type_Explosion_First_Level;
			break;

		case ePlayerBullet_Type_Second_Level:
			_bulletType = ePlayerBullet_Type_Explosion_Second_Level;
			break;

		default: break;
	}

	changeBullet(_bulletState, _bulletType);
}

void PlayerBullet::loadSprite()
{
	m_pBullet = new Animation(Define::ROCKMAN_BULLET, 1, 1, 8, 6);
	m_pBulletLevel1 = new Animation(Define::ROCKMAN_BULLET_LEVEL_1, 1, 5, 46, 24, 0.15f);
	m_pBulletLevel2 = new Animation(Define::ROCKMAN_BULLET_LEVEL_2, 1, 4, 46, 31, 0.15f);
	m_pExplosion = new Animation(Define::ROCKMAN_EXPLOSION, 1, 2, 15, 15, 0.05f);
	m_pExplosionLevel1 = new Animation(Define::ROCKMAN_EXPLOSION_LEVEL_1, 1, 2, 24, 24, 0.05f);
	m_pExplosionLevel2 = new Animation(Define::ROCKMAN_EXPLOSION_LEVEL_2, 1, 2, 24, 26, 0.05f);
}
