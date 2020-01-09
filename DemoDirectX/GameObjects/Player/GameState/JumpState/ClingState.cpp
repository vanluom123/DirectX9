#include "ClingState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


ClingState::ClingState(Player* player, bool dash) :PlayerState(player)
{
	this->_speed = 0.0f;
	this->_countPress = 0.0f;
	this->m_pPlayer->setVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	this->_accelerateY = 15.0f;

	this->_pressed = dash;
}

ClingState::~ClingState()
{
	// Do nothing
}

void ClingState::update(float dt)
{
	if (this->m_pPlayer->getVy() > 0)
		this->m_pPlayer->setState(new FallState(this->m_pPlayer, this->_pressed));
}

void ClingState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	this->_countPress += dt;
	if (this->_countPress < 0.25f)
	{
		if (this->m_pPlayer->getReverse())
		{
			this->_speed = Define::PLAYER_MAX_CLING_SPEED;

			if (keys[VK_RIGHT])
				this->_countPress = 0.25;
		}
		else
		{
			this->_speed = -Define::PLAYER_MAX_CLING_SPEED;

			if (keys[VK_LEFT])
				this->_countPress = 0.25;
		}
		this->m_pPlayer->setVx(this->_speed);
		this->m_pPlayer->addVy(this->_accelerateY);
		return;
	}

	if (keys[VK_RIGHT])
	{
		this->m_pPlayer->setReverse(false);

		if (this->_pressed)
			this->_speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			this->_speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		this->m_pPlayer->setReverse(true);
		if (this->_pressed)
			this->_speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			this->_speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}
	this->m_pPlayer->setVx(this->_speed);
	this->m_pPlayer->addVy(this->_accelerateY);
}

void ClingState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case Enumerator::Side_Collision::LEFT:
		case Enumerator::Side_Collision::RIGHT:
		{
			Sound::getInstance()->play("JumpUp", false, 1);
			Sound::getInstance()->setVolume(95);

			this->m_pPlayer->setState(new SlipDownState(this->m_pPlayer));
			break;
		}
		case Enumerator::Side_Collision::TOP:
		{
			this->m_pPlayer->setState(new FallState(this->m_pPlayer, this->_pressed));
			break;
		}
		case Enumerator::Side_Collision::BOTTOM:
		{
			this->m_pPlayer->setState(new StandState(this->m_pPlayer));
			break;
		}
		default: break;
	}
}

Player_State ClingState::getState()
{
	return Enumerator::Player_State::CLING;
}
