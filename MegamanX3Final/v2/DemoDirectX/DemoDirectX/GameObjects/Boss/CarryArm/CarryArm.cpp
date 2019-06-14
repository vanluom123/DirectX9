#include "CarryArm.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"

CarryArm::CarryArm()
{
	_objectType = eObjectType::ENEMY;
	_vx = 0.0f;
	_vy = 0.0f;
	_pAnim = new Animation(Define::CARRY_ARM, 3, 10, 44, 65, 0.15f, D3DCOLOR_XRGB(255, 0, 220));
	this->setWidth(_pAnim->getWidth());
	this->setHeight(_pAnim->getHeight());
	_pAnimDie = new Animation(Define::BURST, 1, 9, 50, 45);
	_pAnimDie->setPause(true);
	_curState = eCarryArmState::CARRY_ARM_NONE;
	setState(eCarryArmState::CARRY_ARM_STAND);
	_MaxHP = 5;
	_HP = _MaxHP;
	_Damage = 3;
}

CarryArm::~CarryArm()
{
	delete _pAnim;
	delete _pAnimDie;
}

void CarryArm::draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotateCenter, D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	if (!_isDie)
	{
		_pAnim->setPosition(getPosition());
		_pAnim->draw(_pAnim->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);
	}
	if (!_pAnimDie->getPause())
		_pAnimDie->draw(_pAnimDie->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);
}

RECT CarryArm::getBound()
{
	RECT boundingBox;

	switch (_curState)
	{
	case eCarryArmState::CARRY_ARM_EVENT_MOVE_UP_2:
		boundingBox.left = _posX - 43 / 2.0f;
		boundingBox.right = 43 + boundingBox.left;
		boundingBox.top = _posY - 59 / 2.0f;
		boundingBox.bottom = 59 + boundingBox.top;
		break;

	default:
		boundingBox.left = _posX - 36 / 2.0f;
		boundingBox.right = boundingBox.left + 36;
		boundingBox.top = _posY - 57 / 2.0f;
		boundingBox.bottom = boundingBox.top + 57;
		break;
	}

	return boundingBox;
}

void CarryArm::update(float dt)
{
	_pAnim->update(dt);
	BaseObject::update(dt);
	_pAnimDie->update(dt);
	updateState(dt);
}

void CarryArm::onCollision(BaseObject* obj)
{
	if (obj->getObjectType() == eObjectType::ROCK_MAN_BULLET && !_isDie)
	{
		_HP -= obj->getDamage();
		if (_HP <= 0)
		{
			_HP = _MaxHP;
			_isDie = true;
			_pAnimDie->setPosition(getPosition());
			_pAnimDie->setAnimation(0, 10, 0.05f, false);
			setState(eCarryArmState::CARRY_ARM_STAND);
		}
	}
}

void CarryArm::setState(eCarryArmState state)
{
	if (_curState == state)
		return;

	_curState = state;

	switch (state)
	{
	case eCarryArmState::CARRY_ARM_STAND:
	case eCarryArmState::CARRY_ARM_MOVE_DOWN:
	case eCarryArmState::CARRY_ARM_MOVE_UP:
		_pAnim->setAnimation(0, 10, 0.05f);
		break;

	case eCarryArmState::CARRY_ARM_EVENT_MOVE_UP:
		_pAnim->setAnimation(1, 5, 0.05f, false);
		break;

	case eCarryArmState::CARRY_ARM_EVENT_MOVE_UP_2:
		_pAnim->setAnimation(2, 5, 0.05f, false);
		break;

	default:
		break;
	}
}

void CarryArm::updateState(float dt)
{
	switch (_curState)
	{
	case eCarryArmState::CARRY_ARM_STAND:
		_posX = 4880;
		_posY = 1500;
		_vx = 0;
		_vy = 0;
		break;

	case eCarryArmState::CARRY_ARM_MOVE_DOWN:
		_vx = 0;
		_vy = 80;
		if (_posY > _starty)
			setState(eCarryArmState::CARRY_ARM_EVENT_MOVE_UP_2);
		break;

	case eCarryArmState::CARRY_ARM_MOVE_UP:
		_vx = 80;
		_vy = -30;
		if (_posX > _startx)
			setState(eCarryArmState::CARRY_ARM_STAND);
		break;

	case eCarryArmState::CARRY_ARM_EVENT_MOVE_UP:
		_vx = 0;
		_vy = 0;
		if (_pAnim->getPause())
			setState(eCarryArmState::CARRY_ARM_MOVE_UP);
		break;

	case eCarryArmState::CARRY_ARM_EVENT_MOVE_UP_2:
		_vx = 0;
		_vy = 0;
		if (_pAnim->getPause())
			setState(eCarryArmState::CARRY_ARM_EVENT_MOVE_UP);
		break;

	default: break;
	}
}
