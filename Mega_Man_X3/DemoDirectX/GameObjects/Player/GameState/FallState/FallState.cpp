#include "FallState.h"
#include "../RunState/RunState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


FallState::FallState(Player* player, bool dash) :PlayerState(player)
{
	m_pPlayer->setVy(0.0f);
	_accelerateY = 25.0f;
	_pressed = dash;
}

FallState::~FallState()
{
}

void FallState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
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

	if (m_pPlayer->getVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		m_pPlayer->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void FallState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case eSide_Left:
		case eSide_Right:
		{
			m_pPlayer->setState(new SlipDownState(m_pPlayer));
			break;
		}
		case eSide_Bottom:
		{
			Sound::getInstance()->play("FallDownGround", false, 1);
			Sound::getInstance()->setVolume(95);
			m_pPlayer->setState(new StandState(m_pPlayer));
			break;
		}
		default:
			break;
	}
}

Player_State FallState::getState()
{
	return ePlayer_Fall;
}
