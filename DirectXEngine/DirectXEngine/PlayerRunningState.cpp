#include "PlayerRunningState.h"
#include "GameDefine.h"
#include "PlayerStandingState.h"

PlayerRunningState::PlayerRunningState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
	acceleratorX = 25.0f;

	this->mPlayerData->player->allowMoveToLeft = true;
	this->mPlayerData->player->allowMoveToRight = true;
}


void PlayerRunningState::HandlerKeyBoard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		this->mPlayerData->player->SetReverse(false); //Move to right don't reverse sprite

		if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED) //Vx < 180 move to right
		{
			this->mPlayerData->player->AddVx(acceleratorX); //Sum Vx = Vx + acceleratorX

			if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED) //Vx > 180 reset Vx = 180
				this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
		}
	}
	else if (keys[VK_LEFT])
	{
		this->mPlayerData->player->SetReverse(true);

		if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->mPlayerData->player->AddVx(-acceleratorX);

			if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
				this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
		}
	}
	else
		this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
}

PlayerState::StateName PlayerRunningState::GetState()
{
	return Running;
}

void PlayerRunningState::OnCollision(Entity* Impact, Entity::CollisionReturn data, Entity::SideCollision side)
{
	switch (side)
	{
		case Entity::Left:
		{
			if (this->mPlayerData->player->goMoveDirection() == Player::Left)
			{
				this->mPlayerData->player->allowMoveToLeft = false;
				this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			}
			return;
		}
		case Entity::Right:
		{
			if (this->mPlayerData->player->goMoveDirection() == Player::Right)
			{
				this->mPlayerData->player->allowMoveToRight = false;
				this->mPlayerData->player->AddPosition(data.RegionCollision.left - data.RegionCollision.right, 0);
				this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
			}
			return;
		}
		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
		{
			this->mPlayerData->player->AddPosition(0, data.RegionCollision.top - data.RegionCollision.bottom);
			this->mPlayerData->player->SetVy(0);
			return;
		}
		case Entity::Top: break;
		case Entity::TopLeft: break;
		case Entity::TopRight: break;
		case Entity::Unknown: break;
		default: break;
	}
}

PlayerRunningState::~PlayerRunningState()
{}
