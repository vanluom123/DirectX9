#include "PlayerState.h"


void PlayerState::Update(float dt)
{}

void PlayerState::HandlerKeyBoard(std::map<int, bool> keys)
{}

PlayerState::~PlayerState()
{}

PlayerState::PlayerState(PlayerData* playerData)
{
	mPlayerData = playerData;
}

PlayerState::PlayerState()
{}
