#include "AppearState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


AppearState::AppearState(Player* player) : PlayerState(player)
{
	this->_accelerateY = 25.0f;
}

AppearState::~AppearState()
{
	// Do something
}

void AppearState::update(float dt)
{
	if (this->m_pPlayer->getAnimation()->getCurrentColumn() == 0)
		this->m_pPlayer->getAnimation()->setPause(true);
	else if (this->m_pPlayer->getAnimation()->getCurrentColumn() >= 4)
		this->m_pPlayer->setState(new StandState(this->m_pPlayer));
}

void AppearState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	this->m_pPlayer->setVx(0.0f);
	this->m_pPlayer->addVy(this->_accelerateY);

	if (this->m_pPlayer->getVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		this->m_pPlayer->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void AppearState::onCollision(Side_Collision side)
{
	if (side == Enumerator::Side_Collision::BOTTOM)
		this->m_pPlayer->getAnimation()->setPause(false);
}

Player_State AppearState::getState()
{
	return Enumerator::Player_State::APPEAR;
}
