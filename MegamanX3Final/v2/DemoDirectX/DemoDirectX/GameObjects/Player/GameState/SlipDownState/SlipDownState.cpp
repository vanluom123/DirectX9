#include "SlipDownState.h"
#include "../StandState/StandState.h"
#include "../FallState/FallState.h"
#include "../../../../GameDefines/GameDefine.h"


SlipDownState::SlipDownState(PLAYERDATA* playerData) :PlayerState(playerData)
{
	_playerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
	_isSlide = true;
}

void SlipDownState::Update(float dt)
{
	if (!_isSlide)
		_playerData->player->SetState(new FallState(_playerData));

	_isSlide = false;
}

void SlipDownState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	_playerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
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
		_playerData->player->SetState(new FallState(_playerData));
	}
}

void SlipDownState::OnCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::LEFT:
	case BaseObject::RIGHT:
	{
		_isSlide = true;
		break;
	}
	case BaseObject::BOTTOM:
	{
		_playerData->player->SetState(new StandState(_playerData));
		break;
	}
	default: break;
	}
}

Player::ePlayerState SlipDownState::GetState()
{
	return Player::SLIP_DOWN;
}
