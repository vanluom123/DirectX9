#include "StandState.h"
#include "../RunState/RunState.h"
#include "../../../../GameDefines/GameDefine.h"


StandState::StandState(PLAYERDATA* playerData) :PlayerState(playerData)
{
	_playerData->player->SetVx(0);
	_timeStand = 0.0f;
	_isMove = false;
}

void StandState::Update(float dt)
{
	_timeStand += dt;
	if (_timeStand > 1.50f)
	{
		_playerData->player->GetAnimation()->SetAnimation(1, 4, 0.1, false);
		_timeStand = 0.0f;
	}

	if (_isMove)
		_playerData->player->SetState(new RunState(_playerData));
}

void StandState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	_playerData->player->SetVx(0);
	_playerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	_isMove = false;

	if (keys[VK_RIGHT])
	{
		_isMove = true;
		_playerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		_isMove = true;
		_playerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
}

void StandState::OnCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::LEFT:
	case BaseObject::RIGHT:
	{
		_isMove = false;
	}
	default: break;
	}
}

Player::ePlayerState StandState::GetState()
{
	return Player::STAND;
}
