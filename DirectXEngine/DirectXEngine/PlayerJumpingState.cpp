#include "PlayerJumpingState.h"
#include "GameDefine.h"
#include "PlayerFallingState.h"


PlayerJumpingState::PlayerJumpingState(PlayerData* playerData)
{
	mPlayerData = playerData;
	mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);

	isPressed = false;

	acceleratorX = 14.0f;
	acceleratorY = 15.0f;
}

PlayerJumpingState::~PlayerJumpingState()
{}

void PlayerJumpingState::Update(float dt)
{
	// PLAYER_MAX_JUMP_VELOCITY + acceleratorY nó sẽ rớt xuống
	mPlayerData->player->AddVy(acceleratorY); 

	// PLAYER_MAX_JUMP_VELOCITY + acceleratorY >= 0 thì nó sẽ set trạng											thái Falling của nhân vật
	if (mPlayerData->player->GetVy() >= 0) 
	{
		// Switch State
		mPlayerData->player->SetState(new PlayerFallingState(mPlayerData)); 
		return;
	}

	//Khi nguoi choi khong con nhan
	if (!isPressed)
	{
		// Neu no di chuyen sang trai
		if (mPlayerData->player->goMoveDirection() == Player::MoveToLeft)
		{
			// Neu Vx < 0 cai nay luon dung vi di chuyen sang trai Vx se luon luon < 0
			if (mPlayerData->player->GetVx() < 0)
			{
				// Vx += acceleratorX de Vx > 0
				mPlayerData->player->AddVx(acceleratorX);

				// Vx > 0 thi minh reset Vx = 0
				if (mPlayerData->player->GetVx() > 0)
				{
					// Reset Vx = 0
					mPlayerData->player->SetVx(0);
				}
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

		if (mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED) // Vx < 180 move to right
		{
			mPlayerData->player->AddVx(acceleratorX); // Sum Vx = Vx + acceleratorX

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

void PlayerJumpingState::OnCollision(Entity* impact, Entity::CollisionReturn data, Entity::SideCollision side)
{
	switch (side)
	{
		case Player::Left:
		{
			this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
			this->mPlayerData->player->SetVx(0);
			break;
		}
		case Player::Right:
		{
			this->mPlayerData->player->AddPosition(data.RegionCollision.left - data.RegionCollision.right, 0);
			this->mPlayerData->player->SetVx(0);
		}
		case Player::Top: case Player::TopLeft: case Player::TopRight:
		{
			this->mPlayerData->player->AddPosition(0, data.RegionCollision.bottom - data.RegionCollision.top);
			this->mPlayerData->player->SetVy(0);
			break;
		}
		case Player::Bottom: case Player::BottomLeft: case Player::BottomRight:
		{
			this->mPlayerData->player->AddPosition(0, data.RegionCollision.top - data.RegionCollision.bottom);
			break;
		}
		case Entity::Unknown: break;
		default: break;
	}
}

PlayerState::StateName PlayerJumpingState::GetState()
{
	return Jumping;
}
