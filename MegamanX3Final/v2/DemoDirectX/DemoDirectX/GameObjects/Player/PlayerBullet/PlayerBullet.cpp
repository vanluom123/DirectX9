#include "PlayerBullet.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"

PlayerBullet::PlayerBullet()
{
	_objectType = ROCK_MAN_BULLET;
	_bulletX = 25.0f;
}

PlayerBullet::~PlayerBullet()
{
	SAFE_DELETE(_animation_bullet);
}

void PlayerBullet::newBullet(float bx, float by, bool direction, eBulletType type)
{
	_posX = bx;
	_posY = by;
	_isAllowDraw = true;
	_isExplosion = false;
	_bulletState = BULLET_STATE_FIRE;
	_bulletType = type;

	setReverse(direction);
	if (direction == true)
		_vx = -300.0f;
	else
		_vx = 300.0f;

	this->changeBullet(BULLET_STATE_FIRE, type);
}

void PlayerBullet::changeBullet(eBulletState state, eBulletType type)
{
	switch (state)
	{
	case BULLET_STATE_FIRE:
	{
		switch (type)
		{
		case BULLET_TYPE_NORMAL:
		{
			_Damage = 1;
			_animation_bullet = new Animation("Resources/rockman/bullet.png", 1, 1, 8, 6);
		}
		break;

		case BULLET_TYPE_FIRST_LEVEL:
		{
			_Damage = 2;
			_animation_bullet = new Animation("Resources/rockman/bullet_level_1.png", 1, 5, 46, 24, 0.15f);
		}
		break;

		case BULLET_TYPE_SECOND_LEVEL:
		{
			_Damage = 4;
			_animation_bullet = new Animation("Resources/rockman/bullet_level_2.png", 1, 4, 46, 31, 0.15f);
		}
		break;

		default: break;
		}
	}
	case BULLET_STATE_EXPLOSION:
	{
		switch (type)
		{
		case BULLET_TYPE_EXPLOSION_NORMAL:
		{
			_animation_bullet = new Animation("Resources/rockman/explosions_bullet.png", 1, 2, 15, 15, 0.05f);
			_animation_bullet->setLoop(false);
		}
		break;

		case BULLET_TYPE_EXPLOSION_FIRST_LEVEL:
		{
			_animation_bullet = new Animation("Resources/rockman/explosion_level_1.png", 1, 2, 24, 24, 0.05f);
			_animation_bullet->isAnchorPoint(true);
			if (_isReverse)
				_animation_bullet->setAnchorPoint(1.0f, 1.0f);
			else
				_animation_bullet->setAnchorPoint(1.0f, 1.0f);
			_animation_bullet->setLoop(false);
		}
		break;

		case BULLET_TYPE_EXPLOSION_SECOND_LEVEL:
		{
			_animation_bullet = new Animation("Resources/rockman/explosions_level_2.png", 1, 2, 24, 26, 0.05f);
			_animation_bullet->setLoop(false);
		}
		break;

		default: break;
		}
	}

	default: break;

	}

	_width = _animation_bullet->getWidth();
	_height = _animation_bullet->getHeight();
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
		_animation_bullet->setPosition(getPosition());

		if (camera != nullptr)
			_animation_bullet->draw(getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
		else
			_animation_bullet->draw(getPosition());
	}
}

void PlayerBullet::update(float dt)
{
	if (_isAllowDraw)
	{
		if (_animation_bullet->getPause())
		{
			_isAllowDraw = false;
		}

		BaseObject::update(dt);
		_animation_bullet->update(dt);
	}
}

void PlayerBullet::onCollision(eSideCollision side)
{
	// Do nothing
}

void PlayerBullet::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() != ENEMY
		&& obj->getObjectType() != BOSS
		&& obj->getObjectType() != BOX)
		return;

	if (obj->getHP() <= 0)
		return;

	_isExplosion = true;
	_vx = _vy = 0.0f;
	_bulletState = BULLET_STATE_EXPLOSION;

	switch (_bulletType)
	{
	case BULLET_TYPE_NORMAL:
	{
		_bulletType = BULLET_TYPE_EXPLOSION_NORMAL;
		break;
	}

	case BULLET_TYPE_FIRST_LEVEL:
	{
		_bulletType = BULLET_TYPE_EXPLOSION_FIRST_LEVEL;
		break;
	}

	case BULLET_TYPE_SECOND_LEVEL:
	{
		_bulletType = BULLET_TYPE_EXPLOSION_SECOND_LEVEL;
		break;
	}

	default: break;
	}

	changeBullet(_bulletState, _bulletType);
}