#include "AppearState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


AppearState::AppearState(PLAYERDATA* playerData) : PlayerState(playerData)
{
	_accelerateY = 25.0f;
}

void AppearState::Update(float dt)
{
	if (_playerData->player->GetAnimation()->GetCurrentColumn() == 0)
		_playerData->player->GetAnimation()->SetPause(true);
	else if (_playerData->player->GetAnimation()->GetCurrentColumn() >= 4)
		_playerData->player->SetState(new StandState(_playerData));
}

void AppearState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	_playerData->player->SetVx(0);
	_playerData->player->AddVy(_accelerateY);

	if (_playerData->player->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		_playerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void AppearState::OnCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::BOTTOM:
		_playerData->player->GetAnimation()->SetPause(false);
		break;

	default: break;
	}
}

Player::ePlayerState AppearState::GetState()
{
	return Player::APPEAR;
}
