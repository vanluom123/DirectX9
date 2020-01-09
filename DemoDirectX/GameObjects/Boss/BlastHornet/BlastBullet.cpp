#include "BlastBullet.h"
#include "../../../GameComponents/Camera.h"
#include "../../Player/PlayerBullet/PlayerBullet.h"
#include "../../../GameComponents/GameCollision.h"

BlastBullet::BlastBullet() : _timeDelay(0.0f)
{
	this->loadSprite();
	this->_objectType = Enumerator::Object_Type::ENEMY_BULLET;
	this->_isReverse = true;
	this->_Damage = 3;
	this->_MaxHP = 4;
	this->_HP = this->_MaxHP;
	this->_pCurrentAnim = nullptr;
	this->setState(Enumerator::EnemyBullet_State::FIRE);
}

void BlastBullet::loadSprite()
{
	_pAnim = new Animation(Define::BULLET_BLAST_HORNET, 1, 3, 24, 22, 0.05f, D3DCOLOR_XRGB(6, 113, 158));
	_pAnimExplosion = new Animation(Define::EXPLOSION_BLAST_HORNET, 1, 6, 34, 34, 0.05f, D3DCOLOR_XRGB(6, 113, 158));
}

Player* BlastBullet::getPlayer() const { return this->m_pPlayer; }

void BlastBullet::setPlayer(Player* val) { this->m_pPlayer = val; }

BlastBullet::~BlastBullet()
{
	delete this->_pAnim;
	delete this->_pAnimExplosion;
}

RECT BlastBullet::getBound()
{
	RECT bound;
	bound.left = _posX - this->_width / 2;
	bound.top = _posY - this->_height / 2;
	bound.right = bound.left + this->_width;
	bound.bottom = bound.top + this->_height;
	return bound;
}

void BlastBullet::newObject()
{
	this->loadSprite();

	if (!this->_isReverse)
	{
		this->setReverse(true);
		this->setVx(-80.0f);
		this->setVy(50.0f);
	}
	else
	{
		this->setReverse(false);
		this->setVx(80.0f);
		this->setVy(50.0f);
	}

	this->_timeDelay = 0.0f;
	this->_isDestroy = false;
	this->_isAllowDraw = true;
	this->setState(Enumerator::EnemyBullet_State::FIRE);
}

void BlastBullet::update(float dt)
{
	this->_timeDelay += dt;

	this->m_towardsPlayer.x = this->m_pPlayer->getPosition().x - this->getPosition().x;
	this->m_towardsPlayer.y = this->m_pPlayer->getPosition().y - this->getPosition().y;
	D3DXVec2Normalize(&m_towardsPlayer, &m_towardsPlayer);

	this->_vx = this->m_towardsPlayer.x * 125.0f;
	this->_vy = this->m_towardsPlayer.y * 125.0f;

	if (this->_isAllowDraw)
	{
		if (this->_pCurrentAnim->getPause() && this->_isDestroy)
			this->_isAllowDraw = false;

		this->_pCurrentAnim->update(dt);
		BaseObject::update(dt);
	}
}

void BlastBullet::onCollision(Side_Collision side)
{
	this->_vx = 0.0f;
	this->_vy = 0.0f;
}

void BlastBullet::onCollision(BaseObject* obj)
{
	this->_vx = 0.0f;
	this->_vy = 0.0f;

	if (this->_isDestroy) return;

	if (obj->getObjectType() == Enumerator::Object_Type::ROCKMAN_BULLET)
	{
		this->_isDestroy = true;
		this->setState(Enumerator::EnemyBullet_State::EXPLOSION);
	}
	else if (obj->getObjectType() == Enumerator::Object_Type::ROCKMAN)
	{
		this->_isDestroy = true;
		this->setState(Enumerator::EnemyBullet_State::EXPLOSION);
	}
	else
	{
		if (this->_timeDelay > 1.5f)
		{
			this->_timeDelay = 0.0f;
			this->_isDestroy = true;
			this->setState(Enumerator::EnemyBullet_State::EXPLOSION);
		}
	}
}

void BlastBullet::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter, D3DCOLOR color)
{
	if (this->_isAllowDraw)
	{
		this->_pCurrentAnim->setPosition(this->getPosition());
		this->_pCurrentAnim->setReverse(this->_isReverse);
		if (camera)
			this->_pCurrentAnim->draw(this->_pCurrentAnim->getPosition(), rect, scale, camera->getTrans(), 0, rotationCenter, color);
		else
			this->_pCurrentAnim->draw(this->_pCurrentAnim->getPosition());
	}
}

void BlastBullet::setState(EnemyBullet_State state)
{
	this->_bulletState = state;
	this->changeAnimation(state);
}

void BlastBullet::changeAnimation(EnemyBullet_State state)
{
	switch (state)
	{
		case Enumerator::EnemyBullet_State::EXPLOSION:
			this->_pCurrentAnim = this->_pAnimExplosion;
			this->_pCurrentAnim->setAnimation(0, 6, 0.05f, false);
			break;

		case Enumerator::EnemyBullet_State::FIRE:
			this->_pCurrentAnim = this->_pAnim;
			this->_pCurrentAnim->setAnimation(0, 3);
			break;

		default:
			break;
	}

	this->_width = this->_pCurrentAnim->getWidth();
	this->_height = this->_pCurrentAnim->getHeight();
}