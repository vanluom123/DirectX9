#include "JumpState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"


JumpState::JumpState(Player* player) :PlayerState(player)
{
	Sound::getInstance()->play("JumpUp", false, 1);
	Sound::getInstance()->setVolume(95);

	this->m_pPlayer->setVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	this->_accelerateY = 15.0f;
	this->_timePress = 0;
	this->_pressed = false;

	if (this->m_pPlayer->getPlayerState()->getState() == Enumerator::Player_State::DASH)
		this->_pressed = true;
}

JumpState::~JumpState()
{
}

void JumpState::update(float dt)
{
	if (this->m_pPlayer->getVy() > 0)
		this->m_pPlayer->setState(new FallState(this->m_pPlayer, this->_pressed));
}

void JumpState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	// Exception collide
	this->_timePress += dt;
	float speed = 0.0f;

	if (keys[VK_RIGHT])
	{
		this->m_pPlayer->setReverse(false);

		if (this->_pressed)
			speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		this->m_pPlayer->setReverse(true);
		if (this->_pressed)
			speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}

	this->m_pPlayer->setVx(speed);
	this->m_pPlayer->addVy(_accelerateY);
}

void JumpState::onCollision(Side_Collision side)
{
	switch (side)
	{
		case Enumerator::Side_Collision::LEFT:
		case Enumerator::Side_Collision::RIGHT:
		{
			if (this->_timePress < 0.3f)
				break;
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
		default:
			break;
	}
}

Player_State JumpState::getState()
{
	return Enumerator::Player_State::JUMP;
}
