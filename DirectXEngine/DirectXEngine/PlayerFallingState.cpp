#include "PlayerFallingState.h"
#include "PlayerStandingState.h"
#include "Player.h"
#include "GameDefine.h"
#include "PlayerRunningState.h"

PlayerFallingState::PlayerFallingState(PlayerData* playerData) : isLeftOrRightKeyPressed(false)
{
	this->mPlayerData = playerData;
	acceleratorX = 8.0f;
	acceleratorY = 15.0f;

	if (this->mPlayerData->player->GetVx() == 0)
		allowMoveX = false;
	else allowMoveX = true;
}

PlayerFallingState::~PlayerFallingState()
{
}

void PlayerFallingState::Update(float dt)
{
	this->mPlayerData->player->AddVy(acceleratorY);

	if (this->mPlayerData->player->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		this->mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void PlayerFallingState::HandlerKeyBoard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetReverse(false);

		if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(acceleratorX);

			if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
				this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
		}

		isLeftOrRightKeyPressed = true;
	}
	else if (keys[VK_LEFT])
	{
		this->mPlayerData->player->SetReverse(true);

		if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(-acceleratorX);

			if (this->mPlayerData->player->GetVx() <= -Define::PLAYER_MAX_RUNNING_SPEED)
				this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
		}

		isLeftOrRightKeyPressed = true;
	}
	else isLeftOrRightKeyPressed = false;
}

void PlayerFallingState::OnCollision(Entity* impact, Entity::CollisionReturn data, Entity::SideCollision side)
{
	switch (side)
	{
		case Entity::Left:
		{
			if (this->mPlayerData->player->goMoveDirection() == Player::MoveToLeft)
			{
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				this->mPlayerData->player->SetVx(0);
			}
			break;
		}
		case Entity::Right:
		{
			if (this->mPlayerData->player->goMoveDirection() == Player::MoveToRight)
			{
				this->mPlayerData->player->AddPosition(data.RegionCollision.left - data.RegionCollision.right, 0);
				this->mPlayerData->player->SetVx(0);
			}
			break;
		}
		case Entity::Top: case Entity::TopLeft: case Entity::TopRight: break;
		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
		{
			if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
			{
				this->mPlayerData->player->AddPosition(0, data.RegionCollision.top - data.RegionCollision.bottom);
				if (isLeftOrRightKeyPressed)
					this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
				else
					this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			}
		}
		case Entity::Unknown: break;
		default: break;
	}
}

PlayerState::StateName PlayerFallingState::GetState()
{
	return Falling;
}
