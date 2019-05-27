#include "CarryArm.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"

CarryArm::CarryArm()
{
	_objectType = eObjectType::ENEMY;
	_vx = 0;
	_vy = 0;
	_pAnim = new Animation(Define::CARRY_ARM, 3, 10, 44, 65, 0.15, D3DCOLOR_XRGB(255, 0, 220));
	_pAnimDie = new Animation(Define::BURST, 1, 9, 50, 45);
	_pAnimDie->SetPause(true);
	_curState = eCarryArmState::CARRY_ARM_NONE;
	SetState(eCarryArmState::CARRY_ARM_STAND);
	_MaxHP = 5;
	_HP = _MaxHP;
	_Damage = 3;
}

CarryArm::~CarryArm()
{
	delete _pAnim;
	delete _pAnimDie;
}

void CarryArm::Draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotateCenter, D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	if (!_isDie)
	{
		_pAnim->SetPosition(GetPosition());
		_pAnim->Draw(_pAnim->GetPosition(), r, scale, camera->GetTrans(), angle, rotateCenter, color);
	}
	if (!_pAnimDie->GetPause())
		_pAnimDie->Draw(_pAnimDie->GetPosition(), r, scale, camera->GetTrans(), angle, rotateCenter, color);
}

RECT CarryArm::GetBound()
{
	RECT bound;

	if (_curState == eCarryArmState::CARRY_ARM_EVENT_MOVE_UP_2)
	{
		bound.left = _posX - 43 / 2.0f;
		bound.right = 43 + bound.left;
		bound.top = _posY - 59 / 2.0f;
		bound.bottom = 59 + bound.top;
	}
	else
	{
		bound.left = _posX - 36 / 2.0f;
		bound.right = bound.left + 36;
		bound.top = _posY - 57 / 2.0f;
		bound.bottom = bound.top + 57;
	}

	return bound;
}

void CarryArm::Update(float dt)
{
	_pAnim->Update(dt);
	BaseObject::Update(dt);
	_pAnimDie->Update(dt);
	UpdateState(dt);
}

void CarryArm::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() == eObjectType::ROCK_MAN_BULLET && !_isDie)
	{
		_HP -= obj->GetDamage();
		if (_HP <= 0)
		{
			_HP = _MaxHP;
			_isDie = true;
			_pAnimDie->SetPosition(GetPosition());
			_pAnimDie->SetAnimation(0, 10, 0.05, false);
			SetState(eCarryArmState::CARRY_ARM_STAND);
		}
	}
}

void CarryArm::SetState(eCarryArmState state)
{
	if (_curState == state)
		return;

	switch (state)
	{
	case eCarryArmState::CARRY_ARM_STAND:
	case eCarryArmState::CARRY_ARM_MOVE_DOWN:
	case eCarryArmState::CARRY_ARM_MOVE_UP:
		_pAnim->SetAnimation(0, 10, 0.05f);
		break;

	case eCarryArmState::CARRY_ARM_EVENT_MOVE_UP:
		_pAnim->SetAnimation(1, 5, 0.05f, false);
		break;

	case eCarryArmState::CARRY_ARM_EVENT_MOVE_UP_2:
		_pAnim->SetAnimation(2, 5, 0.05f, false);
		break;

	default:break;
	}

	SetWidth(_pAnim->GetWidth());
	SetHeight(_pAnim->GetHeight());

	_curState = state;
}

void CarryArm::UpdateState(float dt)
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
			SetState(eCarryArmState::CARRY_ARM_EVENT_MOVE_UP_2);
		break;

	case eCarryArmState::CARRY_ARM_MOVE_UP:
		_vx = 80;
		_vy = -30;
		if (_posX > _startx)
			SetState(eCarryArmState::CARRY_ARM_STAND);
		break;

	case eCarryArmState::CARRY_ARM_EVENT_MOVE_UP:
		_vx = 0;
		_vy = 0;
		if (_pAnim->GetPause())
			SetState(eCarryArmState::CARRY_ARM_MOVE_UP);
		break;

	case eCarryArmState::CARRY_ARM_EVENT_MOVE_UP_2:
		_vx = 0;
		_vy = 0;
		if (_pAnim->GetPause())
			SetState(eCarryArmState::CARRY_ARM_EVENT_MOVE_UP);
		break;

	default: break;
	}
}
