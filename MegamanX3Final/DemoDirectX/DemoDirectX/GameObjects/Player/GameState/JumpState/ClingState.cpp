#include "ClingState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"

ClingState::ClingState(PlayerData* data, bool dash) : GameState(data)
{
	speed = 0.0f;
	countPress = 0;
	pData->GetGamePlayer()->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	translateY = 15.0f;

	Pressed = dash;
}


void ClingState::update(float dt)
{
	if (pData->GetGamePlayer()->GetVy() > 0)
		pData->GetGamePlayer()->SetState(new FallState(pData, Pressed));
}

void ClingState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	countPress += dt;
	if (countPress < 0.25f)
	{
		if (pData->GetGamePlayer()->GetReverse())
		{
			speed = Define::PLAYER_MAX_CLING_SPEED;
			
			if (keys[VK_RIGHT])
				countPress = 0.25;
		}
		else
		{
			speed = -Define::PLAYER_MAX_CLING_SPEED;

			if (keys[VK_LEFT])
				countPress = 0.25;
		}
		pData->GetGamePlayer()->SetVx(speed);
		pData->GetGamePlayer()->AddVy(translateY);
		return;
	}

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

void ClingState::onCollision(Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::LEFT:
	case Entity::RIGHT:
	{
		Sound::getInstance()->play("JumpUp", false, 1);
		Sound::getInstance()->setVolume(95);

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

GamePlayer::StateName ClingState::GetState()
{
	return GamePlayer::CLING;
}
