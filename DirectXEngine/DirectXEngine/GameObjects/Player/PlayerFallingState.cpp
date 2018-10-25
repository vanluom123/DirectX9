#include "PlayerFallingState.h"
#include "Player.h"
#include "PlayerStandingState.h"
#include "../../GameComponents/GameCollision.h"
#include "../../GameDefines/GameDefine.h"
#include "PlayerRunningState.h"

PlayerFallingState::PlayerFallingState(PlayerData *playerData)
{
	this->pData = playerData;
	acceleratorY = 15.0f;
	acceleratorX = 8.0f;

	if (this->pData->pPlayer->GetVx() == 0)
	{
		allowMoveX = false;
	}
	else
	{
		allowMoveX = true;
	}
}


PlayerFallingState::~PlayerFallingState()
{
}

void PlayerFallingState::Update(float dt)
{
	this->pData->pPlayer->AddVy(acceleratorY);

	if (pData->pPlayer->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
	{
		pData->pPlayer->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	}
}

void PlayerFallingState::HandleKeyboard(std::map<int, bool> keys)
{
	if (keys[VK_RIGHT])
	{
		pData->pPlayer->SetReverse(false);

		isLeftOrRightKeyPressed = true;
		//di chuyen sang phai
		if (this->pData->pPlayer->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->pData->pPlayer->AddVx(acceleratorX);

			if (this->pData->pPlayer->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->pData->pPlayer->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else if (keys[VK_LEFT])
	{
		pData->pPlayer->SetReverse(true);

		isLeftOrRightKeyPressed = true;
		//di chuyen sang trai
		if (this->pData->pPlayer->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			this->pData->pPlayer->AddVx(-acceleratorX);

			if (this->pData->pPlayer->GetVx() <= -Define::PLAYER_MAX_RUNNING_SPEED)
			{
				this->pData->pPlayer->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
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
	//lay phia va cham so voi pPlayer
	//GameCollision::SideCollisions side = GameCollision::GetSideCollision(this->pData->pPlayer, data);

	switch (side)
	{
		case Entity::Left:
			if (pData->pPlayer->getMoveDirection() == Player::MoveToLeft)
			{
				this->pData->pPlayer->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				this->pData->pPlayer->SetVx(0);
			}
			break;

		case Entity::Right:
			if (pData->pPlayer->getMoveDirection() == Player::MoveToRight)
			{
				this->pData->pPlayer->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				this->pData->pPlayer->SetVx(0);
			}
			break;

		case Entity::Top:
			break;

		case Entity::Bottom:
		case Entity::BottomRight:
		case Entity::BottomLeft:
			if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
			{
				this->pData->pPlayer->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

				if (!isLeftOrRightKeyPressed)
					this->pData->pPlayer->SetState(new PlayerStandingState(this->pData));

				this->pData->pPlayer->SetState(new PlayerRunningState(this->pData));
			}
			break;

		default:
			break;
	}
}

PlayerState::StateName PlayerFallingState::GetState()
{
	return PlayerState::Falling;
}
