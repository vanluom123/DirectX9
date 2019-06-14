﻿#include "FallState.h"
#include "../RunState/RunState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


FallState::FallState(PlayerData* playerData, bool dash) :PlayerState(playerData)
{
	_playerData->player->setVy(0.0f);
	_accelerateY = 25.0f;
	_pressed = dash;
}

void FallState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	float speed = 0.0f;
	if (keys[VK_RIGHT])
	{
		_playerData->player->setReverse(false);

		if (_pressed)
			speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		_playerData->player->setReverse(true);
		if (_pressed)
			speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}
	_playerData->player->setVx(speed);

	_playerData->player->addVy(_accelerateY);

	if (_playerData->player->getVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		_playerData->player->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void FallState::onCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
		case BaseObject::LEFT:
		case BaseObject::RIGHT:
			{
				_playerData->player->setState(new SlipDownState(_playerData));
				break;
			}
		case BaseObject::BOTTOM:
			{
				Sound::getInstance()->play("FallDownGround", false, 1);
				Sound::getInstance()->setVolume(95);
				_playerData->player->setState(new StandState(_playerData));
				break;
			}
		default:
			break;
	}
}

Player::ePlayerState FallState::getState()
{
	return Player::FALL;
}
