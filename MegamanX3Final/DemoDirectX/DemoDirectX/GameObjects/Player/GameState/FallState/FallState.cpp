#include "FallState.h"
#include "../RunState/RunState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


FallState::FallState(PLAYERDATA* playerData, bool dash) :PlayerState(playerData)
{
	_playerData->player->SetVy(0);
	_accelerateY = 25.0f;
	_pressed = dash;
}

void FallState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	float speed = 0.0f;
	if (keys[VK_RIGHT])
	{
		_playerData->player->SetReverse(false);

		if (_pressed)
			speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		_playerData->player->SetReverse(true);
		if (_pressed)
			speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}
	_playerData->player->SetVx(speed);

	_playerData->player->AddVy(_accelerateY);

	if (_playerData->player->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		_playerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void FallState::onCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
	case BaseObject::LEFT:
	case BaseObject::RIGHT:
	{
		_playerData->player->SetState(new SlipDownState(_playerData));
		break;
	}
	case BaseObject::BOTTOM:
	{
		Sound::getInstance()->play("FallDownGround", false, 1);
		Sound::getInstance()->setVolume(95);
		_playerData->player->SetState(new StandState(_playerData));
		break;
	}
	default: break;
	}
}

Player::StateName FallState::GetState()
{
	return Player::FALL;
}
