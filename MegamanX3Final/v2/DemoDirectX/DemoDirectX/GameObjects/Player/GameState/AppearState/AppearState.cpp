#include "AppearState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


AppearState::AppearState(Player* player) : PlayerState(player)
{
	_accelerateY = 25.0f;
}

AppearState::~AppearState()
{
}

void AppearState::update(float dt)
{
	if (m_pPlayer->getAnimation()->getCurrentColumn() == 0)
		m_pPlayer->getAnimation()->setPause(true);
	else if (m_pPlayer->getAnimation()->getCurrentColumn() >= 4)
		m_pPlayer->setState(new StandState(m_pPlayer));
}

void AppearState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	m_pPlayer->setVx(0.0f);
	m_pPlayer->addVy(_accelerateY);

	if (m_pPlayer->getVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		m_pPlayer->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void AppearState::onCollision(Side_Collision side)
{
	if (side == eSide_Bottom)
		m_pPlayer->getAnimation()->setPause(false);
}

Player_State AppearState::getState()
{
	return ePlayer_Appear;
}
