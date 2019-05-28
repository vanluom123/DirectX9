#include "PlayerState.h"

PlayerState::PlayerState(PLAYERDATA* playerData)
{
	_playerData = playerData;
}

void PlayerState::Update(float dt) { }

void PlayerState::KeyBoardEventHandler(std::map<int, bool> keys, float dt) { }

void PlayerState::OnCollision(BaseObject::eSideCollision side) { }
