#include "BleedState.hpp"
#include "../StandState/StandState.h"


BleedState::BleedState(PLAYERDATA* playerData, int direction) : PlayerState(playerData)
{
	_playerData->player->SetVx(30.0f * direction);
	_playerData->player->SetVy(5.0f);
	_timeBleed = 0.0f;
}

void BleedState::Update(float dt)
{
	_playerData->player->SetVx(0);
	_playerData->player->GetAnimation()->SetPause(false);

	if (_playerData->player->GetAnimation()->GetCurrentColumn() >= 8)
		_playerData->player->SetState(new StandState(_playerData));
}

Player::ePlayerState BleedState::GetState()
{
	return Player::BLEED;
}
