#include "PlayerJumpingState.h"
#include "GameDefine.h"
#include "PlayerFallingState.h"


PlayerJumpingState::PlayerJumpingState(PlayerData* playerData)
{
	mPlayerData = playerData;
	mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);

	isPressed = false;

	acceleratorX = 5.0f;
	acceleratorY = 6.0f;
}

PlayerJumpingState::~PlayerJumpingState()
{}

void PlayerJumpingState::Update(float dt)
{
	mPlayerData->player->AddVy(acceleratorY); // PLAYER_MAX_JUMP_VELOCITY + acceleratorY nó sẽ rớt xuống

	if (mPlayerData->player->GetVy() >= 0) // PLAYER_MAX_JUMP_VELOCITY + acceleratorY >= 0 thì nó sẽ set trạng thái Falling của nhân vật
	{
		mPlayerData->player->SetState(new PlayerFallingState(mPlayerData)); // Switch State
		return;
	}

	if (!isPressed) //Khi nguoi choi khong con nhan
	{
		if (mPlayerData->player->goMoveDirection() == Player::MoveToLeft) //Neu no di chuyen sang trai
		{
			if (mPlayerData->player->GetVx() < 0) //Neu Vx < 0 cai nay luon dung vi di chuyen sang trai Vx se luon luon < 0
			{
				mPlayerData->player->AddVx(acceleratorX); //Vx += acceleratorX de Vx > 0
				if (mPlayerData->player->GetVx() > 0) //Vx > 0 thi minh reset Vx = 0
					mPlayerData->player->SetVx(0); //Reset Vx = 0
			}
		}
		else if (mPlayerData->player->goMoveDirection() == Player::MoveToRight)
		{
			if (mPlayerData->player->GetVx() > 0)
			{
				mPlayerData->player->AddVx(-acceleratorX);
				if (mPlayerData->player->GetVx() < 0)
					mPlayerData->player->SetVx(0);
			}
		}
	}
}

void PlayerJumpingState::HandlerKeyBoard(std::map<int, bool> keys)
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

		isPressed = true;
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

		isPressed = true;
	}
	else isPressed = false;
}

PlayerState::StateName PlayerJumpingState::GetState()
{
	return Jumping;
}
