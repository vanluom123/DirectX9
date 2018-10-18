#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"

class PlayerRunningState;

PlayerStandingState::PlayerStandingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}


PlayerStandingState::~PlayerStandingState()
{}

void PlayerStandingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_LEFT] || keys[VK_RIGHT])
		this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
}

PlayerState::StateName PlayerStandingState::GetState()
{
    return PlayerState::Standing;
}
