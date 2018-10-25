#include "PlayerStandingState.h"
#include "Player.h"
#include "PlayerRunningState.h"

PlayerStandingState::PlayerStandingState(PlayerData *pData)
{
    this->pData = pData;
    this->pData->pPlayer->SetVx(0);
    this->pData->pPlayer->SetVy(0);
}


PlayerStandingState::~PlayerStandingState()
{}

void PlayerStandingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_LEFT] || keys[VK_RIGHT])
		this->pData->pPlayer->SetState(new PlayerRunningState(this->pData));
}

PlayerState::StateName PlayerStandingState::GetState()
{
    return PlayerState::Standing;
}
