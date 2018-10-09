#include "PlayerRunningState.h"
#include "GameDefine.h"
#include "PlayerStandingState.h"

PlayerRunningState::PlayerRunningState(PlayerData* playerData)
{
	mPlayerData = playerData;
	acceleratorX = 8.0f;
}

void PlayerRunningState::Update(float dt)
{}

void PlayerRunningState::HandlerKeyBoard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false); //Move to right don't reverse sprite

		if (mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED) //Vx < 180 move to right
		{
			mPlayerData->player->AddVx(acceleratorX); //Sum Vx = Vx + acceleratorX
			
			if (mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED) //Vx > 180 reset Vx = 180
				mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
		}
	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);

		if (mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			mPlayerData->player->AddVx(-acceleratorX);
			
			if (mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
				mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
		}
	}
	else
		mPlayerData->player->SetState(new PlayerStandingState(mPlayerData));
}

PlayerState::StateName PlayerRunningState::GetState()
{
	return Running;
}

PlayerRunningState::~PlayerRunningState()
{}
