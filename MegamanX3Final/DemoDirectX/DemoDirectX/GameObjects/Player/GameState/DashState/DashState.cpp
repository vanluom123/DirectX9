#include "DashState.h"
#include <iostream>
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"

DashState::DashState(PlayerData* data) : GameState(data)
{
	Sound::getInstance()->play("dash", false, 1);
	Sound::getInstance()->setVolume(95);
	translateX = 25.0f;
	timePress = 0;
}

void DashState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	pData->GetGamePlayer()->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);

	timePress += dt;
	if (timePress <= 0.45f)
	{
		if (!pData->GetGamePlayer()->GetReverse())
		{
			pData->GetGamePlayer()->SetVx(Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_LEFT])
				pData->GetGamePlayer()->SetState(new StandState(pData));
		}
		else
		{
			pData->GetGamePlayer()->SetVx(-Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_RIGHT])
				pData->GetGamePlayer()->SetState(new StandState(pData));
		}
	}
	else
		pData->GetGamePlayer()->SetState(new StandState(pData));
}

void DashState::onCollision(Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::LEFT:
	case Entity::RIGHT:
		{
			Sound::getInstance()->stop("dash");
			pData->GetGamePlayer()->SetState(new StandState(pData));
			break;
		}
	default: break;
	}
}

GamePlayer::StateName DashState::GetState()
{
	return GamePlayer::DASH;
}
