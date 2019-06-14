#include "JumpState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


JumpState::JumpState(PlayerData* playerData) :PlayerState(playerData)
{
	Sound::getInstance()->play("JumpUp", false, 1);
	Sound::getInstance()->setVolume(95);

	_playerData->player->setVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	_accelerateY = 15.0f;
	_timePress = 0;
	_pressed = false;

	if (_playerData->state->getState() == Player::DASH)
		_pressed = true;
}

void JumpState::Update(float dt)
{
	if (_playerData->player->getVy() > 0)
		_playerData->player->setState(new FallState(_playerData, _pressed));
}

void JumpState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	// Exception collide
	_timePress += dt;
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
}

void JumpState::onCollision(BaseObject::eSideCollision side)
{
	switch (side)
	{
		case BaseObject::LEFT:
		case BaseObject::RIGHT:
			{
				if (_timePress < 0.3f)
					break;
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

Player::ePlayerState JumpState::getState()
{
	return Player::JUMP;
}
