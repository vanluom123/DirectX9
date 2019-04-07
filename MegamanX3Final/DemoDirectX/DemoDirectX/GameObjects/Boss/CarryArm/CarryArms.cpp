#include "CarryArms.h"
#include "../../../GameDefines/GameDefine.h"
#include "../../../GameComponents/GameCollision.h"

CarryArms::CarryArms()
{
	tag = Tag::ENEMY;
	vx = 0;
	vy = 0;
	anim = new Animation(Define::CARRY_ARM, 3, 10, 44, 65, 0.15, D3DCOLOR_XRGB(255, 0, 220));
	pAnimationDie = new Animation(Define::BURST, 1, 9, 50, 45);
	pAnimationDie->setPause(true);
	curState = CarryArmsState::NONE;
	SetState(CarryArmsState::STAND);
	MaxHP = 5;
	HP = MaxHP;
	Damage = 3;
}

CarryArms::~CarryArms()
{
	delete anim;
	delete pAnimationDie;
}

void CarryArms::Draw(Camera* camera, RECT r, D3DXVECTOR2 scale, float angle, D3DXVECTOR2 rotateCenter, D3DCOLOR color)
{
	if (!allowDraw)
		return;

	if (!isDie)
	{
		anim->setPosition(GetPosition());
		anim->draw(anim->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);
	}
	if (!pAnimationDie->getPause())
		pAnimationDie->draw(pAnimationDie->getPosition(), r, scale, camera->getTrans(), angle, rotateCenter, color);
}

RECT CarryArms::GetBound()
{
	long left, top, right, bottom;

	if (curState == CarryArmsState::EVENT_MOVE_UP_2)
	{
		left = x - 43 / 2.0f;
		right = 43 + left;
		top = y - 59 / 2.0f;
		bottom = 59 + top;
	}
	else
	{
		left = x - 36 / 2.0f;
		right = left + 36;
		top = y - 57 / 2.0f;
		bottom = top + 57;
	}

	return { left, top, right, bottom };
}

void CarryArms::Update(float dt)
{
	anim->update(dt);
	Entity::Update(dt);
	pAnimationDie->update(dt);
	ManageState(dt);
}

void CarryArms::OnCollision(Entity* obj)
{
	if (obj->GetTag() == Tag::ROCK_MAN_BULLET && !isDie)
	{
		HP -= obj->GetDamage();
		if (HP <= 0)
		{
			HP = MaxHP;
			isDie = true;
			pAnimationDie->setPosition(GetPosition());
			pAnimationDie->setAnimation(0, 10, 0.05, false);
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
		anim->setAnimation(0, 10, 0.05f);
		break;

	case CarryArmsState::EVENT_MOVE_UP:
		anim->setAnimation(1, 5, 0.05f, false);
		break;

	case CarryArmsState::EVENT_MOVE_UP_2:
		anim->setAnimation(2, 5, 0.05f, false);
		break;

	default:break;
	}

	SetWidth(anim->getWidth());
	SetHeight(anim->getHeight());

	curState = state;
}

void CarryArms::ManageState(float dt)
{
	switch (curState)
	{
	case CarryArmsState::STAND:
		x = 4880;
		y = 1500;
		vx = 0;
		vy = 0;
		break;

	case CarryArmsState::MOVE_DOWN:
		vx = 0;
		vy = 80;
		if (y > starty)
			SetState(CarryArmsState::EVENT_MOVE_UP_2);
		break;

	case CarryArmsState::MOVE_UP:
		vx = 80;
		vy = -30;
		if (x > startx)
			SetState(CarryArmsState::STAND);
		break;

	case CarryArmsState::EVENT_MOVE_UP:
		vx = 0;
		vy = 0;
		if (anim->getPause())
			SetState(CarryArmsState::MOVE_UP);
		break;

	case CarryArmsState::EVENT_MOVE_UP_2:
		vx = 0;
		vy = 0;
		if (anim->getPause())
			SetState(CarryArmsState::EVENT_MOVE_UP);
		break;

	default: break;
	}
}
