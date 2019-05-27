#include "PlayerState.h"

PlayerState::PlayerState(PLAYERDATA* playerData)
{
	_playerData = playerData;
}

void PlayerState::update(float dt) { }

void PlayerState::handlerKeyBoard(std::map<int, bool> keys, float dt) { }

void PlayerState::onCollision(BaseObject::eSideCollision side) { }
