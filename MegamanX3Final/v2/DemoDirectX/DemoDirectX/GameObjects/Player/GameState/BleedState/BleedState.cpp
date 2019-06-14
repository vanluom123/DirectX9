#include "BleedState.hpp"
#include "../StandState/StandState.h"


BleedState::BleedState(PlayerData* playerData, int direction) : PlayerState(playerData)
{
	_playerData->player->setVx(30.0f * direction);
	_playerData->player->setVy(5.0f);
	_timeBleed = 0.0f;
}

void BleedState::Update(float dt)
{
	_playerData->player->setVx(0.0f);
	_playerData->player->getAnimation()->setPause(false);

	if (_playerData->player->getAnimation()->getCurrentColumn() >= 8)
		_playerData->player->setState(new StandState(_playerData));
}

Player::ePlayerState BleedState::getState()
{
	return Player::BLEED;
}
