#include "CarryArms.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"

CarryArms::CarryArms()
{
	_objectType = eObjectType::ENEMY;
	_vx = 0;
	_vy = 0;
	anim = new Animation(Define::CARRY_ARM, 3, 10, 44, 65, 0.15, D3DCOLOR_XRGB(255, 0, 220));
	pAnimationDie = new Animation(Define::BURST, 1, 9, 50, 45);
	pAnimationDie->SetPause(true);
	curState = CarryArmsState::NONE;
	SetState(CarryArmsState::STAND);
	_MaxHP = 5;
	_HP = _MaxHP;
	_Damage = 3;
}

CarryArms::~CarryArms()
{
	delete anim;
	delete pAnimationDie;
}

void CarryArms::Draw(Camera* camera, RECT r, GVec2 scale, float angle, GVec2 rotateCenter, D3DCOLOR color)
{
	if (!_isAllowDraw)
		return;

	if (!_isDie)
	{
		anim->SetPosition(GetPosition());
		anim->Draw(anim->GetPosition(), r, scale, camera->GetTrans(), angle, rotateCenter, color);
	}
	if (!pAnimationDie->GetPause())
		pAnimationDie->Draw(pAnimationDie->GetPosition(), r, scale, camera->GetTrans(), angle, rotateCenter, color);
}

RECT CarryArms::GetBound()
{
	long left, top, right, bottom;

	if (curState == CarryArmsState::EVENT_MOVE_UP_2)
	{
		left = _posX - 43 / 2.0f;
		right = 43 + left;
		top = _posY - 59 / 2.0f;
		bottom = 59 + top;
	}
	else
	{
		left = _posX - 36 / 2.0f;
		right = left + 36;
		top = _posY - 57 / 2.0f;
		bottom = top + 57;
	}

	return { left, top, right, bottom };
}

void CarryArms::Update(float dt)
{
	anim->Update(dt);
	BaseObject::Update(dt);
	pAnimationDie->Update(dt);
	ManageState(dt);
}

void CarryArms::OnCollision(BaseObject* obj)
{
	if (obj->GetObjectType() == eObjectType::ROCK_MAN_BULLET && !_isDie)
	{
		_HP -= obj->GetDamage();
		if (_HP <= 0)
		{
			_HP = _MaxHP;
			_isDie = true;
			pAnimationDie->SetPosition(GetPosition());
			pAnimationDie->SetAnimation(0, 10, 0.05, false);
			SetState(CarryArmsState::STAND);
		}
	}
}

void CarryArms::SetState(CarryArmsState state)
{
	if (curState == state)
		return;

	switch (state)
	{
	case CarryArmsState::STAND:
	case CarryArmsState::MOVE_DOWN:
	case CarryArmsState::MOVE_UP:
		anim->SetAnimation(0, 10, 0.05f);
		break;

	case CarryArmsState::EVENT_MOVE_UP:
		anim->SetAnimation(1, 5, 0.05f, false);
		break;

	case CarryArmsState::EVENT_MOVE_UP_2:
		anim->SetAnimation(2, 5, 0.05f, false);
		break;

	default:break;
	}

	SetWidth(anim->GetWidth());
	SetHeight(anim->GetHeight());

	curState = state;
}

void CarryArms::ManageState(float dt)
{
	switch (curState)
	{
	case CarryArmsState::STAND:
		_posX = 4880;
		_posY = 1500;
		_vx = 0;
		_vy = 0;
		break;

	case CarryArmsState::MOVE_DOWN:
		_vx = 0;
		_vy = 80;
		if (_posY > _starty)
			SetState(CarryArmsState::EVENT_MOVE_UP_2);
		break;

	case CarryArmsState::MOVE_UP:
		_vx = 80;
		_vy = -30;
		if (_posX > _startx)
			SetState(CarryArmsState::STAND);
		break;

	case CarryArmsState::EVENT_MOVE_UP:
		_vx = 0;
		_vy = 0;
		if (anim->GetPause())
			SetState(CarryArmsState::MOVE_UP);
		break;

	case CarryArmsState::EVENT_MOVE_UP_2:
		_vx = 0;
		_vy = 0;
		if (anim->GetPause())
			SetState(CarryArmsState::EVENT_MOVE_UP);
		break;

	default: break;
	}
}
