#include "PlayerBullet.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"
#include <vector>

PlayerBullet::PlayerBullet()
{
	this->m_pBullet = nullptr;
	this->m_pBulletLevel1 = nullptr;
	this->m_pBulletLevel2 = nullptr;
	this->m_pExplosion = nullptr;
	this->m_pExplosionLevel1 = nullptr;
	this->m_pExplosionLevel2 = nullptr;
	this->m_pCurrentAnimation = nullptr;

	this->loadSprite();
	this->_objectType = Enumerator::Object_Type::ROCKMAN_BULLET;
	this->_bulletX = 25.0f;
	this->_isExplosion = false;
	this->_bulletType = Enumerator::PlayerBullet_Type::BULLET_NORMAL;
	this->_bulletState = Enumerator::PlayerBullet_State::FIRE;
	this->changeBullet(this->_bulletState, this->_bulletType);
}

PlayerBullet::~PlayerBullet()
{
	delete this->m_pBullet;
	delete this->m_pBulletLevel1;
	delete this->m_pBulletLevel2;
	delete this->m_pExplosion;
	delete this->m_pExplosionLevel1;
	delete this->m_pExplosionLevel2;
}

bool PlayerBullet::getExplosion() const
{
	return this->_isExplosion;
}

void PlayerBullet::setBulletX(float bulletX)
{
	this->_bulletX = bulletX;
}

PlayerBullet_Type PlayerBullet::getPlayerBulletType() const
{
	return this->_bulletType;
}

void PlayerBullet::newBullet(float bx, float by, bool direction, PlayerBullet_Type type)
{
	this->loadSprite();
	this->_position.x = bx;
	this->_position.y = by;
	this->_isAllowDraw = true;
	this->_isExplosion = false;
	this->_bulletState = Enumerator::PlayerBullet_State::FIRE;
	this->_bulletType = type;

	this->setReverse(direction);
	this->_velocity.x = (direction) ? -300.0f : 300.0f;

	this->changeBullet(this->_bulletState, type);
}

void PlayerBullet::changeBullet(PlayerBullet_State state, PlayerBullet_Type type)
{
	switch (state)
	{
		case Enumerator::PlayerBullet_State::FIRE:
		{
			switch (type)
			{
				case Enumerator::PlayerBullet_Type::BULLET_NORMAL:
					this->_Damage = 1;
					this->m_pCurrentAnimation = this->m_pBullet;
					break;

				case Enumerator::PlayerBullet_Type::BULLET_FIRST_LEVEL:
					this->_Damage = 2;
					this->m_pCurrentAnimation = this->m_pBulletLevel1;
					break;

				case Enumerator::PlayerBullet_Type::BULLET_SECOND_LEVEL:
					this->_Damage = 4;
					this->m_pCurrentAnimation = this->m_pBulletLevel2;
					break;

				default: break;
			}
		}
		case Enumerator::PlayerBullet_State::EXPLOSION:
		{
			switch (type)
			{
				case Enumerator::PlayerBullet_Type::EXPLOSION_NORMAL:
					this->m_pCurrentAnimation = m_pExplosion;
					this->m_pCurrentAnimation->setLoop(false);
					break;

				case Enumerator::PlayerBullet_Type::EXPLOSION_FIRST_LEVEL:
				{
					this->m_pCurrentAnimation = this->m_pExplosionLevel1;
					this->m_pCurrentAnimation->setLoop(false);

					this->m_pCurrentAnimation->isAnchorPoint(true);
					if (this->_isReverse)
						this->m_pCurrentAnimation->setAnchorPoint(1.0f, 1.0f);
					else
						this->m_pCurrentAnimation->setAnchorPoint(1.0f, 1.0f);

					break;
				}

				case Enumerator::PlayerBullet_Type::EXPLOSION_SECOND_LEVEL:
					this->m_pCurrentAnimation = this->m_pExplosionLevel2;
					this->m_pCurrentAnimation->setLoop(false);
					break;

				default: break;
			}
		}

		default: break;
	}

	this->_width = this->m_pCurrentAnimation->getWidth();
	this->_height = this->m_pCurrentAnimation->getHeight();
}

RECT PlayerBullet::getBound()
{
	RECT bound;
	bound.left = _position.x - _width / 2;
	bound.top = _position.y - _height / 2;
	bound.right = bound.left + _width;
	bound.bottom = bound.top + _height;
	return bound;
}

void PlayerBullet::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	bool checkCollision = GameCollision::getInstance()->AABBCheck(getBound(), camera->getBound());
	
	if (!checkCollision)
	{
		this->_isAllowDraw = false;
		this->_isExplosion = true;;
	}

	if (!this->_isAllowDraw)
		return;

	this->m_pCurrentAnimation->setReverse(this->_isReverse);
	this->m_pCurrentAnimation->setPosition(this->getPosition());
	
	if (camera)
		this->m_pCurrentAnimation->draw(this->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
	else
		this->m_pCurrentAnimation->draw(this->getPosition());
}

void PlayerBullet::update(float dt)
{
	if (this->_isAllowDraw)
	{
		if (this->m_pCurrentAnimation->getPause())
			this->_isAllowDraw = false;

		BaseObject::update(dt);
		this->m_pCurrentAnimation->update(dt);
	}
}

void PlayerBullet::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() != Enumerator::Object_Type::ENEMY
		&& obj->getObjectType() != Enumerator::Object_Type::BOSS
		&& obj->getObjectType() != Enumerator::Object_Type::BOX)
		return;

	if (obj->getHP() <= 0)
		return;

	this->_velocity.x = 0.0f;
	this->_velocity.x = 0.0f;
	this->_isExplosion = true;
	this->_bulletState = Enumerator::PlayerBullet_State::EXPLOSION;

	switch (this->_bulletType)
	{
		case Enumerator::PlayerBullet_Type::BULLET_NORMAL:
			this->_bulletType = Enumerator::PlayerBullet_Type::EXPLOSION_NORMAL;
			break;

		case Enumerator::PlayerBullet_Type::BULLET_FIRST_LEVEL:
			this->_bulletType = Enumerator::PlayerBullet_Type::EXPLOSION_FIRST_LEVEL;
			break;

		case Enumerator::PlayerBullet_Type::BULLET_SECOND_LEVEL:
			this->_bulletType = Enumerator::PlayerBullet_Type::EXPLOSION_SECOND_LEVEL;
			break;

		default: break;
	}

	this->changeBullet(this->_bulletState, this->_bulletType);
}

void PlayerBullet::loadSprite()
{
	this->m_pBullet = new Animation(Define::ROCKMAN_BULLET, 1, 1, 8, 6);
	this->m_pBulletLevel1 = new Animation(Define::ROCKMAN_BULLET_LEVEL_1, 1, 5, 46, 24, 0.15f);
	this->m_pBulletLevel2 = new Animation(Define::ROCKMAN_BULLET_LEVEL_2, 1, 4, 46, 31, 0.15f);
	this->m_pExplosion = new Animation(Define::ROCKMAN_EXPLOSION, 1, 2, 15, 15, 0.05f);
	this->m_pExplosionLevel1 = new Animation(Define::ROCKMAN_EXPLOSION_LEVEL_1, 1, 2, 24, 24, 0.05f);
	this->m_pExplosionLevel2 = new Animation(Define::ROCKMAN_EXPLOSION_LEVEL_2, 1, 2, 24, 26, 0.05f);
}