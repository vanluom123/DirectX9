#include "AppearState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


AppearState::AppearState(PlayerData* playerData) : PlayerState(playerData)
{
	_accelerateY = 25.0f;
}

void AppearState::Update(float dt)
{
	if (_playerData->player->getAnimation()->getCurrentColumn() == 0)
		_playerData->player->getAnimation()->setPause(true);
	else if (_playerData->player->getAnimation()->getCurrentColumn() >= 4)
		_playerData->player->setState(new StandState(_playerData));
}

void AppearState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	_playerData->player->setVx(0.0f);
	_playerData->player->addVy(_accelerateY);

	if (_playerData->player->getVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		_playerData->player->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void AppearState::onCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
		case BaseObject::BOTTOM:
			{
				_playerData->player->getAnimation()->setPause(false);
				break;
			}

		default: break;
	}
}

Player::ePlayerState AppearState::getState()
{
	return Player::APPEAR;
}
