#include "ClingState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


ClingState::ClingState(PLAYERDATA* playerData, bool dash) :PlayerState(playerData)
{
	_speed = 0.0f;
	_countPress = 0;
	_playerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	_accelerateY = 15.0f;

	_pressed = dash;
}

void ClingState::update(float dt)
{
	if (_playerData->player->GetVy() > 0)
		_playerData->player->SetState(new FallState(_playerData, _pressed));
}

void ClingState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	_countPress += dt;
	if (_countPress < 0.25f)
	{
		if (_playerData->player->GetReverse())
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
		_playerData->player->SetVx(_speed);
		_playerData->player->AddVy(_accelerateY);
		return;
	}

	if (keys[VK_RIGHT])
	{
		_playerData->player->SetReverse(false);

		if (_pressed)
			_speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			_speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		_playerData->player->SetReverse(true);
		if (_pressed)
			_speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			_speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}
	_playerData->player->SetVx(_speed);
	_playerData->player->AddVy(_accelerateY);
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

		_playerData->player->SetState(new SlipDownState(_playerData));
		break;
	}
	case BaseObject::TOP:
	{
		_playerData->player->SetState(new FallState(_playerData, _pressed));
		break;
	}
	case BaseObject::BOTTOM:
	{
		_playerData->player->SetState(new StandState(_playerData));
		break;
	}
	default: break;
	}
}

Player::StateName ClingState::GetState()
{
	return Player::CLING;
}
