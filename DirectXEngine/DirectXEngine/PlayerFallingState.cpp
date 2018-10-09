#include "PlayerFallingState.h"
#include "PlayerStandingState.h"
#include "Player.h"
#include "GameDefine.h"

PlayerFallingState::PlayerFallingState(PlayerData* playerData)
{
	mPlayerData = playerData;
	acceleratorX = 10.0f;
	acceleratorY = 3.0f;

	if (mPlayerData->player->GetVx() == 0)
		allowMoveX = false;
	else allowMoveX = true;
}

PlayerFallingState::~PlayerFallingState()
{}

void PlayerFallingState::Update(float dt)
{
	mPlayerData->player->AddVy(acceleratorY);

	if (mPlayerData->player->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void PlayerFallingState::HandlerKeyBoard(std::map<int, bool> keys)
{
	if(keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);

		if(mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			mPlayerData->player->AddVx(acceleratorX);

			if (mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
				mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
		}

		isLeftOrRightKeyPressed = true;
	}
	else if(keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);

		if(mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			mPlayerData->player->AddVx(-acceleratorX);

			if (mPlayerData->player->GetVx() <= -Define::PLAYER_MAX_RUNNING_SPEED)
				mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
		}

		isLeftOrRightKeyPressed = true;
	}
	else isLeftOrRightKeyPressed = false;
}

PlayerState::StateName PlayerFallingState::GetState()
{
	return Falling;
}
