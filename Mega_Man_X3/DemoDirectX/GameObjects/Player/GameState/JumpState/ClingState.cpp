#include "ClingState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


ClingState::ClingState(Player* player, bool dash) :PlayerState(player)
{
	_speed = 0.0f;
	_countPress = 0.0f;
	m_pPlayer->setVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	_accelerateY = 15.0f;

	_pressed = dash;
}

ClingState::~ClingState()
{
}

void ClingState::update(float dt)
{
	if (m_pPlayer->getVy() > 0)
		m_pPlayer->setState(new FallState(m_pPlayer, _pressed));
}

void ClingState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	_countPress += dt;
	if (_countPress < 0.25f)
	{
		if (m_pPlayer->getReverse())
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
		m_pPlayer->setVx(_speed);
		m_pPlayer->addVy(_accelerateY);
		return;
	}

	if (keys[VK_RIGHT])
	{
		m_pPlayer->setReverse(false);

		if (_pressed)
			_speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			_speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		m_pPlayer->setReverse(true);
		if (_pressed)
			_speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			_speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}
	m_pPlayer->setVx(_speed);
	m_pPlayer->addVy(_accelerateY);
}

void ClingState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case eSide_Left:
		case eSide_Right:
		{
			Sound::getInstance()->play("JumpUp", false, 1);
			Sound::getInstance()->setVolume(95);

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

Player_State ClingState::getState()
{
	return ePlayer_Cling;
}
