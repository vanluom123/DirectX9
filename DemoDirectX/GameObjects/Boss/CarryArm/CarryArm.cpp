#include "CarryArm.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"

CarryArm::CarryArm()
{
	this->_objectType = Enumerator::Object_Type::ENEMY;
	this->_velocity.x = 0.0f;
	this->_velocity.y = 0.0f;
	this->_pAnim = new Animation(Define::CARRY_ARM, 3, 10, 44, 65, 0.15f, D3DCOLOR_XRGB(255, 0, 220));
	this->setWidth(_pAnim->getWidth());
	this->setHeight(_pAnim->getHeight());
	this->_pAnimDie = new Animation(Define::BURST, 1, 9, 50, 45);
	this->_pAnimDie->setPause(true);
	this->_curState = Enumerator::Carry_State::NONE;
	this->setState(Enumerator::Carry_State::STAND);
	this->_MaxHP = 5;
	this->_HP = this->_MaxHP;
	this->_Damage = 3;
}

CarryArm::~CarryArm()
{
	delete this->_pAnim;
	delete this->_pAnimDie;
}

void CarryArm::draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotateCenter, D3DCOLOR color)
{
	if(this->_isAllowDraw)
	{
		if (!this->_isDestroy)
		{
			this->_pAnim->setPosition(getPosition());
			this->_pAnim->draw(this->_pAnim->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);
		}
		if (!this->_pAnimDie->getPause())
			this->_pAnimDie->draw(this->_pAnimDie->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);
	}
}

RECT CarryArm::getBound()
{
	RECT boundingBox;

	switch (this->_curState)
	{
		case Enumerator::Carry_State::EVENT_MOVE_UP_2:
			boundingBox.left = _position.x - 43 / 2.0f;
			boundingBox.right = 43 + boundingBox.left;
			boundingBox.top = _position.y - 59 / 2.0f;
			boundingBox.bottom = 59 + boundingBox.top;
			break;

		default:
			boundingBox.left = _position.x - 36 / 2.0f;
			boundingBox.right = boundingBox.left + 36;
			boundingBox.top = _position.y - 57 / 2.0f;
			boundingBox.bottom = boundingBox.top + 57;
			break;
	}

	return boundingBox;
}

void CarryArm::update(float dt)
{
	this->_pAnim->update(dt);
	BaseObject::update(dt);
	this->_pAnimDie->update(dt);
	this->updateState(dt);
}

void CarryArm::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == Enumerator::Object_Type::ROCKMAN_BULLET && !_isDestroy)
	{
		this->_HP -= obj->getDamage();
		if (this->_HP <= 0)
		{
			this->_HP = this->_MaxHP;
			this->_isDestroy = true;
			this->_pAnimDie->setPosition(getPosition());
			this->_pAnimDie->setAnimation(0, 10, 0.05f, false);
			this->setState(Enumerator::Carry_State::STAND);
		}
	}
}

void CarryArm::setState(Carry_State state)
{
	if (this->_curState == state)
		return;

	this->_curState = state;

	switch (state)
	{
		case Enumerator::Carry_State::STAND:
		case Enumerator::Carry_State::MOVE_DOWN:
		case Enumerator::Carry_State::MOVE_UP:
			this->_pAnim->setAnimation(0, 10, 0.05f);
			break;

		case Enumerator::Carry_State::EVENT_MOVE_UP:
			this->_pAnim->setAnimation(1, 5, 0.05f, false);
			break;

		case Enumerator::Carry_State::EVENT_MOVE_UP_2:
			this->_pAnim->setAnimation(2, 5, 0.05f, false);
			break;

		default:
			break;
	}
}

Carry_State CarryArm::getState() { return this->_curState; }

void CarryArm::updateState(float dt)
{
	switch (this->_curState)
	{
		case Enumerator::Carry_State::STAND:
			this->_position.x = 4880.0f;
			this->_position.y = 1500.0f;
			this->_velocity.x = 0.0f;
			this->_velocity.y = 0.0f;
			break;

		case Enumerator::Carry_State::MOVE_DOWN:
			this->_velocity.x = 0.0f;
			this->_velocity.y = 80.0f;
			if (this->_position.y > this->_startPosition.y)
				this->setState(Enumerator::Carry_State::EVENT_MOVE_UP_2);
			break;

		case Enumerator::Carry_State::MOVE_UP:
			this->_velocity.x = 80.0f;
			this->_velocity.y = -30.0f;
			if (this->_position.x > this->_startPosition.x)
				this->setState(Enumerator::Carry_State::STAND);
			break;

		case Enumerator::Carry_State::EVENT_MOVE_UP:
			this->_velocity.x = 0.0f;
			this->_velocity.y = 0.0f;
			if (_pAnim->getPause())
				this->setState(Enumerator::Carry_State::MOVE_UP);
			break;

		case Enumerator::Carry_State::EVENT_MOVE_UP_2:
			this->_velocity.x = 0.0f;
			this->_velocity.y = 0.0f;
			if (this->_pAnim->getPause())
				this->setState(Enumerator::Carry_State::EVENT_MOVE_UP);
			break;

		default: break;
	}
}
