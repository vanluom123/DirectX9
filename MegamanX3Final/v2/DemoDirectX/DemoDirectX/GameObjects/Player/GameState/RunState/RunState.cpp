#include "RunState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


RunState::RunState(PLAYERDATA* playerData):PlayerState(playerData)
{
}

void RunState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	_playerData->player->GetAnimation()->SetPause(false);
	_playerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	if (keys[VK_RIGHT])
	{
		_playerData->player->SetReverse(false);
		_playerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		_playerData->player->SetReverse(true);
		_playerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else
	{
		_playerData->player->SetVx(0);
		_playerData->player->SetState(new StandState(_playerData));
	}
}

void RunState::OnCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::LEFT:
	case BaseObject::RIGHT:
		_playerData->player->SetState(new StandState(_playerData));
		break;
	default: break;
	}
}

Player::ePlayerState RunState::GetState()
{
	return Player::RUN;
}
