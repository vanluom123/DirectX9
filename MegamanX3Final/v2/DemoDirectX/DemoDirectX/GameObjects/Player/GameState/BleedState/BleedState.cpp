#include "BleedState.hpp"
#include "../StandState/StandState.h"


BleedState::BleedState(Player* player, int direction) : PlayerState(player)
{
	m_pPlayer->setVx(30.0f * direction);
	m_pPlayer->setVy(5.0f);
	_timeBleed = 0.0f;
}

BleedState::~BleedState()
{
}

void BleedState::update(float dt)
{
	m_pPlayer->setVx(0.0f);
	m_pPlayer->getAnimation()->setPause(false);

	if (m_pPlayer->getAnimation()->getCurrentColumn() >= 8)
		m_pPlayer->setState(new StandState(m_pPlayer));
}

Player_State BleedState::getState()
{
	return ePlayer_Bleed;
}
