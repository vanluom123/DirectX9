#include "Port.h"
#include "../../GameComponents/GameCollision.h"

// INCLUDE PLAYER AND PLAYER'S STATE
#include "../Player/Player.h"
#include "../Player/GameState/StandState/StandState.h"


Port::Port()
{
	this->_objectType = Enumerator::Object_Type::PORT;
	this->_pAnim = new Animation("Resources/MapObject/Port.png", 1, 17, 16, 48, 0.1f);

	this->_pAnim->setAnimation(0, 1);
	this->_isReverse = false;
	this->_isDestroy = false;
	this->_isAllowDraw = true;
	this->_isOpen = false;
	this->_isClose = false;
	this->_isMove = false;
	this->_HP = 0;
	this->_Damage = 0;
	this->_vx = 0.0f;
	this->_vy = 0.0f;
}

Port::~Port()
{
	delete this->_pAnim;
}

RECT Port::getBound()
{
	if (!this->_isOpen)
		return BaseObject::getBound();

	RECT bound;
	bound.left = this->_posX - this->_width;
	bound.right = this->_posX + this->_height;
	bound.top = this->_posY - this->_height/2;
	bound.bottom = this->_posY + this->_height / 2;
	return bound;
}

void Port::update(float dt)
{
	if (this->_pAnim->getPause() && this->_isOpen)
	{
		if (this->_isClose)
		{
			this->_HP = 2;
			this->_Damage = 1;
			this->_isOpen = false;
			this->_isMove = false;
			this->_pAnim->setAnimation(0, 1);
			
		}
		else
		{
			this->_isMove = true;
			this->_Damage = 1;
		}
	}

	this->_pAnim->update(dt);
}

void Port::onCollision(Side_Collision side)
{}

void Port::onCollision(BaseObject* obj)
{
	if ((obj->getObjectType() != Enumerator::Object_Type::ROCKMAN)
		|| (_HP > 0)
		|| (obj->getBound().top < this->getBound().top))
	{
		return;
	}

	if ((!this->_isOpen) && (!this->_isClose))
	{
		this->_HP = -1;
		this->_isOpen = true;
		this->_isMove = false;
		this->_Damage = 0;
		this->_pAnim->setAnimation(0, 17, 0.1f, false);
	}

	if (this->_isMove)
	{
		if (obj->getReverse())
			obj->setVx(-40.0f);
		else
			obj->setVx(40.0f);

		this->_bound.top = this->_posY - this->_height / 2;
		this->_bound.bottom = this->_posY + this->_height / 2;
		this->_bound.left = this->_posX - 20;
		this->_bound.right = this->_posX + 20;

		if (!GameCollision::getInstance()->AABBCheck(this->_bound, obj->getBound()))
		{
			this->_isClose = true;
			this->_pAnim->setAnimation(1, 17, 0.1f, false);
			this->_isMove = false;
			this->_Damage = 0;

			// Improved DashState of Player when Player was dashing though Port
			auto* player = dynamic_cast<Player*>(obj);
			player->setState(new StandState());
		}
	}
	else
		obj->setVx(0.0f);
}

void Port::draw(Camera* camera, RECT rect, GVec2 scale, float angle, GVec2 rotationCenter,
	D3DCOLOR color)
{
	if (this->_pAnim->getPause())
		return;

	this->_pAnim->setReverse(this->_isReverse);

	this->_pAnim->setPosition(this->_startx - 8, this->_starty);
	this->_pAnim->draw(this->_pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);

	this->_pAnim->setPosition(this->_startx + 8, this->_starty);
	this->_pAnim->draw(this->_pAnim->getPosition(), rect, scale, camera->getTrans(), angle, rotationCenter, color);
}
