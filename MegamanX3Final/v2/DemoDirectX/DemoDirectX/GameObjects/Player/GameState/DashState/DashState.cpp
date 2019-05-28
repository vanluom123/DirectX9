#include "DashState.h"
#include <iostream>
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


DashState::DashState(PLAYERDATA* playerData) :PlayerState(playerData)
{
	Sound::GetInstance()->Play("dash", false, 1);
	Sound::GetInstance()->SetVolume(95);
	_accelerateX = 25.0f;
	_timePress = 0;
}

void DashState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	_playerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);

	_timePress += dt;
	if (_timePress <= 0.45f)
	{
		if (!_playerData->player->GetReverse())
		{
			_playerData->player->SetVx(Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_LEFT])
				_playerData->player->SetState(new StandState(_playerData));
		}
		else
		{
			_playerData->player->SetVx(-Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_RIGHT])
				_playerData->player->SetState(new StandState(_playerData));
		}
	}
	else
		_playerData->player->SetState(new StandState(_playerData));
}

void DashState::OnCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::LEFT:
	case BaseObject::RIGHT:
	{
		Sound::GetInstance()->Stop("dash");
		_playerData->player->SetState(new StandState(_playerData));
		break;
	}
	default: break;
	}
}

Player::ePlayerState DashState::GetState()
{
	return Player::DASH;
}
