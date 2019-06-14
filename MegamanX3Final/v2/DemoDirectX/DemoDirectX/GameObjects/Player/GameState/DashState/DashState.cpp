#include "DashState.h"
#include <iostream>
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


DashState::DashState(PlayerData* playerData) :PlayerState(playerData)
{
	Sound::getInstance()->play("dash", false, 1);
	Sound::getInstance()->setVolume(95);
	_accelerateX = 25.0f;
	_timePress = 0.0f;
}

void DashState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	_playerData->player->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);

	_timePress += dt;
	if (_timePress <= 0.45f)
	{
		if (!_playerData->player->getReverse())
		{
			_playerData->player->setVx(Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_LEFT])
				_playerData->player->setState(new StandState(_playerData));
		}
		else
		{
			_playerData->player->setVx(-Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_RIGHT])
				_playerData->player->setState(new StandState(_playerData));
		}
	}
	else
		_playerData->player->setState(new StandState(_playerData));
}

void DashState::onCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
		case BaseObject::LEFT:
		case BaseObject::RIGHT:
			{
				Sound::getInstance()->stop("dash");
				_playerData->player->setState(new StandState(_playerData));
				break;
			}
		default: break;
	}
}

Player::ePlayerState DashState::getState()
{
	return Player::DASH;
}
