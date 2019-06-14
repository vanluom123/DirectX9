#include "RunState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


RunState::RunState(PlayerData* playerData) :PlayerState(playerData)
{
	_isBoot = false;
}

void RunState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	_playerData->player->getAnimation()->setPause(false);
	_playerData->player->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	if (keys[VK_RIGHT])
	{
		_playerData->player->setReverse(false);
		_playerData->player->setVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		_playerData->player->setReverse(true);
		_playerData->player->setVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else
	{
		_playerData->player->setVx(0.0f);
		_playerData->player->setState(new StandState(_playerData));
	}
}

void RunState::onCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
		case BaseObject::LEFT:
		case BaseObject::RIGHT:
			{
				_playerData->player->setState(new StandState(_playerData));
				break;
			}
		default:
			break;
	}
}

Player::ePlayerState RunState::getState()
{
	return Player::RUN;
}
