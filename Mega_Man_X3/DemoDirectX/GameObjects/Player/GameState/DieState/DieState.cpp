#include "DieState.h"


DieState::DieState(Player* player) : PlayerState(player)
{
	m_pPlayer->setVx(0.0f);
	m_pPlayer->setVy(0.0f);
	_timeDie = 0.0f;
}

DieState::~DieState()
{
}

void DieState::update(float dt)
{
	_timeDie += dt;

	Sound::getInstance()->play("RockmanDie", false, _timeDie);
	Sound::getInstance()->setVolume(95);

	if (_timeDie >= 3.0f)
	{
		m_pPlayer->getAnimation()->setAnimation(20, 3, 0.3f);
		m_pPlayer->setDraw(false);
	}
}

Player_State DieState::getState()
{
	return ePlayer_Death;
}
