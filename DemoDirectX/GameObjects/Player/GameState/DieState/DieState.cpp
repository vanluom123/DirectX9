#include "DieState.h"


DieState::DieState(Player* player) : PlayerState(player)
{
	this->m_pPlayer->setVx(0.0f);
	this->m_pPlayer->setVy(0.0f);
	this->_timeDie = 0.0f;
}

DieState::~DieState()
{
	// Do something
}

void DieState::update(float dt)
{
	this->_timeDie += dt;

	Sound::getInstance()->play("RockmanDie", false, this->_timeDie);
	Sound::getInstance()->setVolume(95);

	if (this->_timeDie >= 3.0f)
	{
		this->m_pPlayer->getAnimation()->setAnimation(20, 3, 0.3f);
		this->m_pPlayer->setDraw(false);
	}
}

Player_State DieState::getState()
{
	return Enumerator::Player_State::DEATH;
}
