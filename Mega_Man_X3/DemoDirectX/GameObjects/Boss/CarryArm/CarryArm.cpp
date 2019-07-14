#include "CarryArm.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"

CarryArm::CarryArm()
{
	_objectType = eObject_Enemy;
	_vx = 0.0f;
	_vy = 0.0f;
	_pAnim = new Animation(Define::CARRY_ARM, 3, 10, 44, 65, 0.15f, D3DCOLOR_XRGB(255, 0, 220));
	this->setWidth(_pAnim->getWidth());
	this->setHeight(_pAnim->getHeight());
	_pAnimDie = new Animation(Define::BURST, 1, 9, 50, 45);
	_pAnimDie->setPause(true);
	_curState = eCarry_None;
	setState(eCarry_Stand);
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
	if(_isAllowDraw)
	{
		if (!_isDie)
		{
			_pAnim->setPosition(getPosition());
			_pAnim->draw(_pAnim->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);
		}
		if (!_pAnimDie->getPause())
			_pAnimDie->draw(_pAnimDie->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);
	}
}

RECT CarryArm::getBound()
{
	RECT boundingBox;

	switch (_curState)
	{
		case eCarry_Event_MoveUp_2:
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
	if (obj->getObjectType() == eObject_RockMan_Bullet && !_isDie)
	{
		_HP -= obj->getDamage();
		if (_HP <= 0)
		{
			_HP = _MaxHP;
			_isDie = true;
			_pAnimDie->setPosition(getPosition());
			_pAnimDie->setAnimation(0, 10, 0.05f, false);
			setState(eCarry_Stand);
		}
	}
}

void CarryArm::setState(Carry_State state)
{
	if (_curState == state)
		return;

	_curState = state;

	switch (state)
	{
		case eCarry_Stand:
		case eCarry_MoveDown:
		case eCarry_MoveUp:
			_pAnim->setAnimation(0, 10, 0.05f);
			break;

		case eCarry_Event_MoveUp:
			_pAnim->setAnimation(1, 5, 0.05f, false);
			break;

		case eCarry_Event_MoveUp_2:
			_pAnim->setAnimation(2, 5, 0.05f, false);
			break;

		default:
			break;
	}
}

Carry_State CarryArm::getState() { return _curState; }

void CarryArm::updateState(float dt)
{
	switch (_curState)
	{
		case eCarry_Stand:
			_posX = 4880.0f;
			_posY = 1500.0f;
			_vx = 0.0f;
			_vy = 0.0f;
			break;

		case eCarry_MoveDown:
			_vx = 0.0f;
			_vy = 80.0f;
			if (_posY > _starty)
				setState(eCarry_Event_MoveUp_2);
			break;

		case eCarry_MoveUp:
			_vx = 80.0f;
			_vy = -30.0f;
			if (_posX > _startx)
				setState(eCarry_Stand);
			break;

		case eCarry_Event_MoveUp:
			_vx = 0.0f;
			_vy = 0.0f;
			if (_pAnim->getPause())
				setState(eCarry_MoveUp);
			break;

		case eCarry_Event_MoveUp_2:
			_vx = 0.0f;
			_vy = 0.0f;
			if (_pAnim->getPause())
				setState(eCarry_Event_MoveUp);
			break;

		default: break;
	}
}
