#include "PlayerBullet.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"

PlayerBullet::PlayerBullet()
{
	_objectType = eObject_RockMan_Bullet;
	_bulletX = 25.0f;
	_isExplosion = false;
	_bulletType = ePlayerBullet_Type_Normal;
	_bulletState = ePlayerBullet_Fire;
	_animation_bullet = nullptr;
}

PlayerBullet::~PlayerBullet()
{
	SAFE_DELETE(_animation_bullet);
}

bool PlayerBullet::getExplosion() const
{
	return _isExplosion;
}

void PlayerBullet::setBulletX(float bulletX)
{
	this->_bulletX = bulletX;
}

void PlayerBullet::newBullet(float bx, float by, bool direction, PlayerBullet_Type type)
{
	_posX = bx;
	_posY = by;
	_isAllowDraw = true;
	_isExplosion = false;
	_bulletState = ePlayerBullet_Fire;
	_bulletType = type;

	setReverse(direction);
	if (direction)
		_vx = -300.0f;
	else
		_vx = 300.0f;

	this->changeBullet(ePlayerBullet_Fire, type);
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
				{
					_Damage = 1;
					_animation_bullet = new Animation(Define::ROCKMAN_BULLET, 1, 1, 8, 6);
				}
				break;

				case ePlayerBullet_Type_First_Level:
				{
					_Damage = 2;
					_animation_bullet = new Animation(Define::ROCKMAN_BULLET_LEVEL_1, 1, 5, 46, 24, 0.15f);
				}
				break;

				case ePlayerBullet_Type_Second_Level:
				{
					_Damage = 4;
					_animation_bullet = new Animation(Define::ROCKMAN_BULLET_LEVEL_2, 1, 4, 46, 31, 0.15f);
				}
				break;

				default: break;
			}
		}
		case ePlayerBullet_Explosion:
		{
			switch (type)
			{
				case ePlayerBullet_Type_Explosion_Normal:
				{
					_animation_bullet = new Animation(Define::ROCKMAN_EXPLOSION, 1, 2, 15, 15, 0.05f);
					_animation_bullet->setLoop(false);
				}
				break;

				case ePlayerBullet_Type_Explosion_First_Level:
				{
					_animation_bullet = new Animation(Define::ROCKMAN_EXPLOSION_LEVEL_1, 1, 2, 24, 24, 0.05f);
					_animation_bullet->isAnchorPoint(true);
					if (_isReverse)
						_animation_bullet->setAnchorPoint(1.0f, 1.0f);
					else
						_animation_bullet->setAnchorPoint(1.0f, 1.0f);
					_animation_bullet->setLoop(false);
				}
				break;

				case ePlayerBullet_Type_Explosion_Second_Level:
				{
					_animation_bullet = new Animation(Define::ROCKMAN_EXPLOSION_LEVEL_2, 1, 2, 24, 26, 0.05f);
					_animation_bullet->setLoop(false);
				}
				break;

				default: break;
			}
		}

		default: break;

	}

	_width = float(_animation_bullet->getWidth());
	_height = float(_animation_bullet->getHeight());
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
		_animation_bullet->setReverse(_isReverse);
		_animation_bullet->setPosition(this->getPosition());

		if (camera)
			_animation_bullet->draw(this->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			_animation_bullet->draw(this->getPosition());
	}
}

void PlayerBullet::update(float dt)
{
	if (_isAllowDraw)
	{
		if (_animation_bullet->getPause())
			_isAllowDraw = false;

		BaseObject::update(dt);
		_animation_bullet->update(dt);
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

	_isExplosion = true;
	_vx = 0.0f;
	_vx = 0.0f;
	_bulletState = ePlayerBullet_Explosion;

	switch (_bulletType)
	{
		case ePlayerBullet_Type_Normal:
		{
			_bulletType = ePlayerBullet_Type_Explosion_Normal;
			break;
		}

		case ePlayerBullet_Type_First_Level:
		{
			_bulletType = ePlayerBullet_Type_Explosion_First_Level;
			break;
		}

		case ePlayerBullet_Type_Second_Level:
		{
			_bulletType = ePlayerBullet_Type_Explosion_Second_Level;
			break;
		}

		default: break;
	}

	changeBullet(_bulletState, _bulletType);
}