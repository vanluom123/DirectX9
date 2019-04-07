#include "JumpState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"

JumpState::JumpState(PlayerData* data) : GameState(data)
{
	Sound::getInstance()->play("JumpUp", false, 1);
	Sound::getInstance()->setVolume(95);

	pData->GetGamePlayer()->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	translateY = 15.0f;
	timePress = 0;
	Pressed = false;
	if (pData->GetGamePlayer()->GetStateName() == GamePlayer::DASH)
		Pressed = true;
}

void JumpState::update(float dt)
{
	if (pData->GetGamePlayer()->GetVy() > 0)
		pData->GetGamePlayer()->SetState(new FallState(pData, Pressed));
}

void JumpState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	timePress += dt; //tranhs loi va cham
	float speed = 0.0f;
	if (keys[VK_RIGHT])
	{
		pData->GetGamePlayer()->SetReverse(false);

		if (Pressed)
			speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		pData->GetGamePlayer()->SetReverse(true);
		if (Pressed)
			speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}
	pData->GetGamePlayer()->SetVx(speed);

	pData->GetGamePlayer()->AddVy(translateY);
}

void JumpState::onCollision(Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::LEFT:
	case Entity::RIGHT:
	{
		if (timePress < 0.3f)
			break;
		pData->GetGamePlayer()->SetState(new SlipDownState(pData));
		break;
	}
	case Entity::TOP:
	{
		pData->GetGamePlayer()->SetState(new FallState(pData, Pressed));
		break;
	}
	case Entity::BOTTOM:
	{
		pData->GetGamePlayer()->SetState(new StandState(pData));
		break;
	}
	default: break;
	}
}

GamePlayer::StateName JumpState::GetState()
{
	return GamePlayer::JUMP;
}
