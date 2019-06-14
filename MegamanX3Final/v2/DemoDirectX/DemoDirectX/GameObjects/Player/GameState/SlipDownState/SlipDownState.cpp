#include "SlipDownState.h"
#include "../StandState/StandState.h"
#include "../FallState/FallState.h"
#include "../../../../GameDefines/GameDefine.h"


SlipDownState::SlipDownState(PlayerData* playerData) :PlayerState(playerData)
{
	_playerData->player->setVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
	_isSlide = true;
}

void SlipDownState::Update(float dt)
{
	if (!_isSlide)
		_playerData->player->setState(new FallState(_playerData));

	_isSlide = false;
}

void SlipDownState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	_playerData->player->setVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
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
		_playerData->player->setState(new FallState(_playerData));
	}
}

void SlipDownState::onCollision(BaseObject::eSideCollision side)
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
				_playerData->player->setState(new StandState(_playerData));
				break;
			}
		default:
			break;
	}
}

Player::ePlayerState SlipDownState::getState()
{
	return Player::SLIP_DOWN;
}
