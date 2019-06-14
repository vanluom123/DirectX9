#include "ClingState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


ClingState::ClingState(PlayerData* playerData, bool dash) :PlayerState(playerData)
{
	_speed = 0.0f;
	_countPress = 0.0f;
	_playerData->player->setVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	_accelerateY = 15.0f;

	_pressed = dash;
}

void ClingState::Update(float dt)
{
	if (_playerData->player->getVy() > 0)
		_playerData->player->setState(new FallState(_playerData, _pressed));
}

void ClingState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	_countPress += dt;
	if (_countPress < 0.25f)
	{
		if (_playerData->player->getReverse())
		{
			_speed = Define::PLAYER_MAX_CLING_SPEED;

			if (keys[VK_RIGHT])
				_countPress = 0.25;
		}
		else
		{
			_speed = -Define::PLAYER_MAX_CLING_SPEED;

			if (keys[VK_LEFT])
				_countPress = 0.25;
		}
		_playerData->player->setVx(_speed);
		_playerData->player->addVy(_accelerateY);
		return;
	}

	if (keys[VK_RIGHT])
	{
		_playerData->player->setReverse(false);

		if (_pressed)
			_speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			_speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		_playerData->player->setReverse(true);
		if (_pressed)
			_speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			_speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}
	_playerData->player->setVx(_speed);
	_playerData->player->addVy(_accelerateY);
}

void ClingState::onCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
		case BaseObject::LEFT:
		case BaseObject::RIGHT:
			{
				Sound::getInstance()->play("JumpUp", false, 1);
				Sound::getInstance()->setVolume(95);

				_playerData->player->setState(new SlipDownState(_playerData));
				break;
			}
		case BaseObject::TOP:
			{
				_playerData->player->setState(new FallState(_playerData, _pressed));
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

Player::ePlayerState ClingState::getState()
{
	return Player::CLING;
}
