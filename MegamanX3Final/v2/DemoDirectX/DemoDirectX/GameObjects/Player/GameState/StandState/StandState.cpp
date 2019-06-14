#include "StandState.h"
#include "../RunState/RunState.h"
#include "../../../../GameDefines/GameDefine.h"


StandState::StandState(PlayerData* playerData) :PlayerState(playerData)
{
	_playerData->player->setVx(0.0f);
	_timeStand = 0.0f;
	_isMove = false;
}

void StandState::Update(float dt)
{
	_timeStand += dt;
	if (_timeStand > 1.50f)
	{
		_playerData->player->getAnimation()->setAnimation(1, 4, 0.1f, false);
		_timeStand = 0.0f;
	}

	if (_isMove)
		_playerData->player->setState(new RunState(_playerData));
}

void StandState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	_playerData->player->setVx(0.0f);
	_playerData->player->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	_isMove = false;

	if (keys[VK_RIGHT])
	{
		_isMove = true;
		_playerData->player->setVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		_isMove = true;
		_playerData->player->setVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
}

void StandState::onCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
		case BaseObject::LEFT:
		case BaseObject::RIGHT:
			{
				_isMove = false;
				break;
			}

		default:
			break;
	}
}

Player::ePlayerState StandState::getState()
{
	return Player::STAND;
}
