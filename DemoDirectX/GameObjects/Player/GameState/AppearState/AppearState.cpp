#include "AppearState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


AppearState::AppearState()
{
	this->_accelerateY = 25.0f;
}

AppearState::~AppearState()
{
	// Do something
}

void AppearState::update(float dt)
{
	if (Player::getInstance()->getAnimation()->getCurrentColumn() == 0)
		Player::getInstance()->getAnimation()->setPause(true);
	else if (Player::getInstance()->getAnimation()->getCurrentColumn() >= 4)
		Player::getInstance()->setState(new StandState());
}

void AppearState::KeyBoardEventHandler(std::map<int, bool> keys, float dt)
{
	Player::getInstance()->setVx(0.0f);
	Player::getInstance()->addVy(this->_accelerateY);

	if (Player::getInstance()->getVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		Player::getInstance()->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void AppearState::onCollision(Side_Collision side)
{
	if (side == Enumerator::Side_Collision::BOTTOM)
		Player::getInstance()->getAnimation()->setPause(false);
}

Player_State AppearState::getState()
{
	return Enumerator::Player_State::APPEAR;
}
