#include "PlayerStandingState.h"
#include "PlayerRunningState.h"

PlayerStandingState::PlayerStandingState(PlayerData* playerData)
{
	mPlayerData = playerData;
	mPlayerData->player->SetVx(0);
	mPlayerData->player->SetVy(0);
}

void PlayerStandingState::Update(float dt)
{}

void PlayerStandingState::HandlerKeyBoard(std::map<int, bool> keys)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
		mPlayerData->player->SetState(new PlayerRunningState(mPlayerData));
}

PlayerState::StateName PlayerStandingState::GetState()
{
	return Standing;
}

PlayerStandingState::~PlayerStandingState()
{}
