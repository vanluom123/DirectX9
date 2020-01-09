#include "BleedState.hpp"
#include "../StandState/StandState.h"


BleedState::BleedState(Player* player, int direction) : PlayerState(player)
{
	this->m_pPlayer->setVx(30.0f * direction);
	this->m_pPlayer->setVy(5.0f);
	this->_timeBleed = 0.0f;
}

BleedState::~BleedState()
{
	// Do something
}

void BleedState::update(float dt)
{
	this->m_pPlayer->setVx(0.0f);
	this->m_pPlayer->getAnimation()->setPause(false);

	if (this->m_pPlayer->getAnimation()->getCurrentColumn() >= 8)
		this->m_pPlayer->setState(new StandState(this->m_pPlayer));
}

Player_State BleedState::getState()
{
	return Enumerator::Player_State::BLEED;
}
