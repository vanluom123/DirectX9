#include "JumpState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


JumpState::JumpState(Player* player) :PlayerState(player)
{
	Sound::getInstance()->play("JumpUp", false, 1);
	Sound::getInstance()->setVolume(95);

	m_pPlayer->setVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	_accelerateY = 15.0f;
	_timePress = 0;
	_pressed = false;

	if (m_pPlayer->getPlayerState()->getState() == ePlayer_Dash)
		_pressed = true;
}

JumpState::~JumpState()
{
}

void JumpState::update(float dt)
{
	if (m_pPlayer->getVy() > 0)
		m_pPlayer->setState(new FallState(m_pPlayer, _pressed));
}

void JumpState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	// Exception collide
	_timePress += dt;
	float speed = 0.0f;

	if (keys[VK_RIGHT])
	{
		m_pPlayer->setReverse(false);

		if (_pressed)
			speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		m_pPlayer->setReverse(true);
		if (_pressed)
			speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}

	m_pPlayer->setVx(speed);
	m_pPlayer->addVy(_accelerateY);
}

void JumpState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case eSide_Left:
		case eSide_Right:
		{
			if (_timePress < 0.3f)
				break;
			m_pPlayer->setState(new SlipDownState(m_pPlayer));
			break;
		}
		case eSide_Top:
		{
			m_pPlayer->setState(new FallState(m_pPlayer, _pressed));
			break;
		}
		case eSide_Bottom:
		{
			m_pPlayer->setState(new StandState(m_pPlayer));
			break;
		}
		default:
			break;
	}
}

Player_State JumpState::getState()
{
	return ePlayer_Jump;
}
