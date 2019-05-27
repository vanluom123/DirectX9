#include "PlayerState.h"

PlayerState::PlayerState(PlayerData* playerData)
{
	m_playerData = playerData;
}

void PlayerState::Update(float dt) { }

void PlayerState::KeyBoardEventHandler(std::map<int, bool> keys, float dt) { }

void PlayerState::OnCollision(BaseObject::eSideCollision side) { }
