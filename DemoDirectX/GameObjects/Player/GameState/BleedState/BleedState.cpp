#include "BleedState.hpp"
#include "../StandState/StandState.h"


BleedState::BleedState(int direction)
{
	Player::getInstance()->setVx(30.0f * direction);
	Player::getInstance()->setVy(5.0f);
	this->_timeBleed = 0.0f;
}

BleedState::~BleedState()
{
	// Do something
}

void BleedState::update(float dt)
{
	Player::getInstance()->setVx(0.0f);
	Player::getInstance()->getAnimation()->setPause(false);

	if (Player::getInstance()->getAnimation()->getCurrentColumn() >= 8)
		Player::getInstance()->setState(new StandState());
}

Player_State BleedState::getState()
{
	return Enumerator::Player_State::BLEED;
}
