#include "PlayerFallingState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "PlayerRunningState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"

class PlayerRunningState;

PlayerFallingState::PlayerFallingState(PlayerData *playerData)
{
	this->mPlayerData = playerData;
	acceleratorY = 15.0f;
	acceleratorX = 8.0f;

	if (this->mPlayerData->player->GetVx() == 0)
		allowMoveX = false;
	else
		allowMoveX = true;
}


PlayerFallingState::~PlayerFallingState()
{}

void PlayerFallingState::Update(float dt)
{
	this->mPlayerData->player->AddVy(acceleratorY);

	if (mPlayerData->player->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
	{
		mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	}
}

void PlayerFallingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		mPlayerData->player->SetReverse(false);

		isLeftOrRightKeyPressed = true;
		//Move to left
		if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(acceleratorX);

			if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else if (keys[VK_LEFT])
	{
		mPlayerData->player->SetReverse(true);

		isLeftOrRightKeyPressed = true;
		//Move to  right
		if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(-acceleratorX);

			if (this->mPlayerData->player->GetVx() <= -Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else
	{
		isLeftOrRightKeyPressed = false;
	}
}

void PlayerFallingState::OnCollision(Entity::SideCollisions side, Entity::CollisionReturn data)
{
	//Getting collision side to with player
	//GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);

	switch (side)
	{
		case Entity::Left:
		{
			if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
			{
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				this->mPlayerData->player->SetVx(0);
			}
			break;
		}
		case Entity::Right:
		{
			if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
			{
				this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				this->mPlayerData->player->SetVx(0);
			}
			break;
		}

		case Entity::Top:
			break;

		case Entity::Bottom:
		case Entity::BottomRight:
		case Entity::BottomLeft:
		{
			if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
			{
				this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

				if (isLeftOrRightKeyPressed)
				{
					this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
				}
				else
				{
					this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
				}
			}
			break;
		}

		default:
			break;
	}
}

PlayerState::StateName PlayerFallingState::GetState()
{
	return PlayerState::Falling;
}
