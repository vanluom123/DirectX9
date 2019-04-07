#include "RunState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


RunState::RunState(PlayerData* data) : GameState(data)
{}

void RunState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	pData->GetGamePlayer()->GetAnimation()->setPause(false);
	pData->GetGamePlayer()->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	if (keys[VK_RIGHT])
	{
		pData->GetGamePlayer()->SetReverse(false);
		pData->GetGamePlayer()->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		pData->GetGamePlayer()->SetReverse(true);
		pData->GetGamePlayer()->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else
	{
		pData->GetGamePlayer()->SetVx(0);
		pData->GetGamePlayer()->SetState(new StandState(pData));
	}
}

void RunState::onCollision(Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::LEFT:
	case Entity::RIGHT:
		pData->GetGamePlayer()->SetState(new StandState(pData));
		break;
	default: break;
	}
}

GamePlayer::StateName RunState::GetState()
{
	return GamePlayer::RUN;
}
